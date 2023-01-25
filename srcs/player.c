/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:50:58 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/25 18:16:45 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

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
                    map[neighbors[i]] != player->team + '0' &&
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

    if (player->x == -1 && player->y == -1 &&
        (env->status == not_started || env->status == in_progress)) {
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
    else if (env->status == in_progress) {
        ret = play_turn(env, player);
    }
    if (env->status == game_over && player->x != -1) {
        ret = player_won;
    }
    else if (env->status == game_over) {
        ret = game_over;
    }
    else if (env->status == interrupted) {
        ret = interrupted;
    }
    return (ret);
}
