/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:50:58 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/23 17:59:25 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

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
                    neighbors[i] < MAP_SIZE && map[neighbors[i]] != EMPTY_TILE &&
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

static t_player    get_ennemy(char *map, t_player *player) {    
    t_player    ennemy;

    ennemy.x = -1;
    ennemy.y = -1;
    for (int i = MAP_INDEX(player->x, player->y);
            i < MAP_LENGTH * MAP_WIDTH && ennemy.x == -1; i++) {
        if (map[i] != player->team + '0' && map[i] != '0') {
            ennemy.y = i / MAP_WIDTH; 
           if (ennemy.y != 0) {
                ennemy.x = i % ennemy.y;
            }
            else {
                ennemy.x = 0;
            }
            ennemy.team = map[i] - '0';
        }
    }
    for (int i = MAP_INDEX(player->x, player->y);
            i >= 0 && ennemy.x == -1; i--) {
        if (map[i] != player->team + '0' && map[i] != '0') {
            ennemy.y = i / MAP_WIDTH;
            if (ennemy.y != 0) {
                ennemy.x = i % ennemy.y;
            }
            else {
                ennemy.x = 0;
            }
            ennemy.team = map[i] - '0';
        }
    }
    return (ennemy);
}

static void    move(char *map, t_player *player, t_player *ennemy) {
    t_player tmp;

    tmp = *player;
    if (player->x > ennemy->x &&
            map[MAP_INDEX(player->x - 1, player-> y)] == EMPTY_TILE) {
        --player->x;
    }
    else if (player->x < ennemy->x &&
            map[MAP_INDEX(player->x + 1, player-> y)] == EMPTY_TILE) {
        ++player->x;
    }
    else if (player->y > ennemy->y &&
            map[MAP_INDEX(player->x, player->y - 1)] == EMPTY_TILE) {
        --player->y;
    }
    else if (player->y < ennemy->y &&
            map[MAP_INDEX(player->x, player->y + 1)] == EMPTY_TILE) {
        ++player->y;
    }
    else {
        
    }
    map[MAP_INDEX(tmp.x, tmp.y)] = EMPTY_TILE;
    map[MAP_INDEX(player->x, player->y)] = player->team + '0';
#ifdef DEBUG
    print_player(__FILE__, __LINE__, player);
#endif    
}

static int play_turn(t_ipc_env *env, t_player *player) {
    int         ret = ok;
    t_player    ennemy;

    if (isdead(env->map, player) == true) {
        ret = ended;
        env->map[MAP_INDEX(player->x, player->y)] = EMPTY_TILE;
    }
    else {
        ennemy = get_ennemy(env->map, player);
#ifdef DEBUG
        print_player(__FILE__, __LINE__, &ennemy);
#endif
        if (ennemy.x != -1) {
            move(env->map, player, &ennemy);
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
    return (ret);
}
