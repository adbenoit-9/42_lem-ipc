/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:50:58 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/22 17:26:43 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

static int play_turn(t_ipc_env *env, t_player *player) {
    int state = 0;
    t_player    ennemy;

    if (isdead(env->map, player) != true) {
        state = DEAD;
        env->map[MAP_INDEX(player->x, player->y)] = EMPTY_TILE;
    }
    else {
        ennemy = get_ennemy(env->map, player);
#ifdef DEBUG
        print_player(__FILE__, __LINE__, player);
        print_player(__FILE__, __LINE__, &ennemy);
#endif
        if (ennemy.x != -1) {
            move(env->map, player, &ennemy);
        }
#ifdef DEBUG
        print_player(__FILE__, __LINE__, player);
#endif
    }
    return (state);
}

int play_game(t_ipc_env *env, t_player *player) {
    int             ret = LEMIPC_OK;
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
    if (env->status == GAME_IN_PROGRESS) {
        ret = play_turn(env, player);
    }
    return (ret);
}
