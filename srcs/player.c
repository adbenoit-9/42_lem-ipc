/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:50:58 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/24 16:39:03 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

t_player index_to_player(int index) {
    t_player player;

    player.y = index / MAP_WIDTH; 
    if (player.y != 0) {
        player.x = index % player.y;
    }
    else {
        player.x = 0;
    }
    return (player);
}

static bool isdead(char *map, t_player *player) {
    bool    isdead = false;
    int     neighbors[8] = {MAP_INDEX(player->x, player->y - 1),   // NORTH
                        MAP_INDEX(player->x, player->y + 1),       // SOUTH
                        MAP_INDEX(player->x + 1, player->y),       // EST
                        MAP_INDEX(player->x - 1, player->y),       // OUEST
                        MAP_INDEX(player->x + 1, player->y - 1),   // NORTH-EST
                        MAP_INDEX(player->x - 1, player->y - 1),   // NORTH-OUEST
                        MAP_INDEX(player->x + 1, player->y + 1),   // SUD-EST
                        MAP_INDEX(player->x - 1, player->y + 1)};  // SUD-OUEST

    for (int i = 0; i < 8 && isdead != true; i++) {
        for (int j = i + 1; j < 8 && isdead != true; j++) {
            if (neighbors[i] >= 0 && neighbors[j] >= 0 && neighbors[i] < MAP_SIZE &&
                    neighbors[j] < MAP_SIZE && map[neighbors[i]] != EMPTY_TILE &&
                    map[neighbors[i]] != player->team &&
                    map[neighbors[i]] == map[neighbors[j]]) {
                isdead = true;
#ifdef DEBUG
                printf("killed by %c\n", map[neighbors[i]]);
#endif
            }
        }
    }
    return (isdead);
}

static void    move(char *map, t_player *player, t_player *target) {
    t_player tmp;
    int     dist[2];
    int     dir[2];

    tmp = *player;
    dist[0] = abs(player->x - target->x);
    dist[1] = abs(player->y - target->y);
    dir[0] = player->x > target->x ? -1 : 1;
    dir[1] = player->y > target->y ? -1 : 1;
    if (dist[0] >= dist[1]) {
        if (map[MAP_INDEX(player->x + dir[0], player-> y)] == EMPTY_TILE) {
           player->x += dir[0]; 
        }
        else if (map[MAP_INDEX(player->x, player-> y + dir[1])] == EMPTY_TILE) {   
           player->y += dir[1]; 
        }
    }
    else if (dist[0] < dist[1]) {
        if (map[MAP_INDEX(player->x, player-> y + dir[1])] == EMPTY_TILE) {   
           player->y += dir[1]; 
        }
        else if (map[MAP_INDEX(player->x + dir[0], player-> y)] == EMPTY_TILE) {
           player->x += dir[0]; 
        }
    }
    map[MAP_INDEX(tmp.x, tmp.y)] = EMPTY_TILE;
    map[MAP_INDEX(player->x, player->y)] = player->team + '0';
#ifdef DEBUG
    print_player(__FILE__, __LINE__, player);
#endif    
}

static int play_turn(t_ipc_env *env, t_player *player) {
    int         ret = ok;
    t_player    target;

    if (isdead(env->map, player) == true) {
        ret = player_lose;
        env->map[MAP_INDEX(player->x, player->y)] = EMPTY_TILE;
    }
    else {
        target = get_target(env, player);
#ifdef DEBUG
        print_player(__FILE__, __LINE__, &target);
#endif
        if (target.x != -1) {
            move(env->map, player, &target);
        }
    }
    return (ret);
}

int play_game(t_ipc_env *env, t_player *player) {
    int             ret = ok;
    struct timeval  tv;

    while (player->x == -1 && player->y == -1) {
        gettimeofday(&tv, NULL);
        if (env->map[MAP_INDEX(tv.tv_sec % MAP_LENGTH, tv.tv_usec % MAP_WIDTH)] == EMPTY_TILE) {
            player->x = tv.tv_sec % MAP_LENGTH;
            player->y = tv.tv_usec % MAP_WIDTH;
#ifdef DEBUG
            print_player(__FILE__, __LINE__, player);
#endif
            env->map[MAP_INDEX(player->x, player->y)] = '0' + player->team;
        }
    }
    if (env->status == in_progress) {
        ret = play_turn(env, player);
    }
    else if (env->status == game_over) {
        ret = player_won;
    }
    else if (env->status == interrupted) {
        ret = interrupted;
    }
    return (ret);
}
