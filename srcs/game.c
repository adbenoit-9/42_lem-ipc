/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:50:58 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/22 13:04:42 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

int game(char *map, t_player *player) {
    int             ret = LEMIPC_OK;
    struct timeval  tv;

    while (player->x == -1 && player->y == -1) {
        gettimeofday(&tv, NULL);
        if (map[MAP_INDEX(tv.tv_sec % MAP_LENGTH, tv.tv_usec % MAP_WIDTH)] == '0') {
            player->x = tv.tv_sec % MAP_LENGTH;
            player->y = tv.tv_usec % MAP_WIDTH;
#ifdef DEBUG
            print_player(__FILE__, __LINE__, player);
#endif
            map[MAP_INDEX(player->x, player->y)] = '0' + player->team;
        }
    }
    if (map[STATUS_INDEX] == GAME_IN_PROGRESS) {
        ret = play(map, player);
    }
    return (ret);
}
