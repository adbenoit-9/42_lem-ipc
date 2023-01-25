/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:50:58 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/25 17:04:30 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

t_player    index_to_player(char *map, int index) {
    t_player player;

    player.y = index / MAP_HEIGH; 
    if (player.y != 0) {
        player.x = index % player.y;
    }
    else {
        player.x = 0;
    }
    player.team = map[index] - '0';
    return (player);
}

int coor_to_index(int x, int y) {
    int index;

    if (x < 0 || y < 0 || x >= MAP_WIDTH || y >= MAP_HEIGH) {
        index = -1;
    }
    else {
        index = MAP_WIDTH * y + x;
    }
    return (index);
}

static bool isdead(char *map, t_player *player) {
    bool    isdead = false;
    int     neighbors[8] = {coor_to_index(player->x, player->y - 1),   // NORTH
                        coor_to_index(player->x, player->y + 1),       // SOUTH
                        coor_to_index(player->x + 1, player->y),       // EST
                        coor_to_index(player->x - 1, player->y),       // OUEST
                        coor_to_index(player->x + 1, player->y - 1),   // NORTH-EST
                        coor_to_index(player->x - 1, player->y - 1),   // NORTH-OUEST
                        coor_to_index(player->x + 1, player->y + 1),   // SUD-EST
                        coor_to_index(player->x - 1, player->y + 1)};  // SUD-OUEST

    for (int i = 0; i < 8 && isdead != true; i++) {
        for (int j = i + 1; j < 8 && isdead != true; j++) {
            if (neighbors[i] != -1 && neighbors[j] != -1 &&
                    map[neighbors[i]] != EMPTY_TILE &&
                    map[neighbors[i]] != player->team &&
                    map[neighbors[i]] == map[neighbors[j]]) {
                isdead = true;
#ifdef LOG
                printf("\033[31m[DEAD] Killed by team %c at (%d, %d)\033[0m\n",
                    map[neighbors[i]], player->x, player->y);
#endif
            }
        }
    }
    return (isdead);
}

static void move(char *map, t_player *player, t_player *target) {
    t_player tmp;
    int     dist[2];
    int     dir[2];

    tmp = *player;
    dist[0] = abs(player->x - target->x);
    dist[1] = abs(player->y - target->y);
    dir[0] = player->x > target->x ? -1 : (player->x < target->x ? 1 : 0);
    dir[1] = player->y > target->y ? -1 : (player->y < target->y ? 1 : 0);
    if (dist[0] > 1 || dist[1] > 1) {
        if (dist[0] > dist[1] || (dist[0] == dist[1] && rand() % 1 == 1)) {
            if (map[coor_to_index(player->x + dir[0], player->y)] == EMPTY_TILE) {
            player->x += dir[0];
            }
            else if (map[coor_to_index(player->x, player->y + dir[1])] == EMPTY_TILE) {   
            player->y += dir[1];
            }
            else if (player->y - dir[1] >= 0 && player->y - dir[1] < MAP_HEIGH &&
                map[coor_to_index(player->x, player->y - dir[1])] == EMPTY_TILE) {
                player->y -= dir[1]; 
            }
            else if (player->x - dir[0] >= 0 && player->x - dir[0] < MAP_HEIGH &&
                map[coor_to_index(player->x, player->x - dir[0])] == EMPTY_TILE) {
                player->x -= dir[0]; 
            }
        }
        else {
            if (map[coor_to_index(player->x, player->y + dir[1])] == EMPTY_TILE) {   
            player->y += dir[1]; 
            }
            else if (map[coor_to_index(player->x + dir[0], player->y)] == EMPTY_TILE) {
            player->x += dir[0]; 
            }
            else if (player->x - dir[0] >= 0 && player->x - dir[0] < MAP_WIDTH &&
                map[coor_to_index(player->x - dir[0], player->y)] == EMPTY_TILE) {
                player->x -= dir[0]; 
            }
            else if (player->y - dir[1] >= 0 && player->y - dir[1] < MAP_HEIGH &&
                map[coor_to_index(player->x, player->y - dir[1])] == EMPTY_TILE) {
                player->y -= dir[1]; 
            }
        }
    }
    map[coor_to_index(tmp.x, tmp.y)] = EMPTY_TILE;
    map[coor_to_index(player->x, player->y)] = player->team + '0';
}

static int  play_turn(t_ipc_env *env, t_player *player) {
    int         ret = ok;
    t_player    target;

    if (isdead(env->map, player) == true) {
        ret = player_lose;
        env->map[coor_to_index(player->x, player->y)] = EMPTY_TILE;
    }
    else {
        target = get_target(env, player);
        if (target.x != -1) {
            move(env->map, player, &target);
        }
    }
    return (ret);
}

int play_game(t_ipc_env *env, t_player *player) {
    int ret = ok;
    int x,y;

    while (player->x == -1 && player->y == -1) {
        x = rand() % MAP_WIDTH;
        y = rand() % MAP_HEIGH;
        if (env->map[coor_to_index(x, y)] == EMPTY_TILE) {
            player->x = x;
            player->y = y;
#ifdef LOG
            printf("\033[33m[INFO] Player of team %d at (%d, %d)\033[0m\n",
                player->team, player->x, player->y);              
#endif
            env->map[coor_to_index(player->x, player->y)] = '0' + player->team;
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
