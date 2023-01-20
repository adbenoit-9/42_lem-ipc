/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemipc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:50:58 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/20 15:41:59 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

int lemipc(char *map, t_player *player) {
    int             ret = LEMIPC_OK;
    struct timeval  tv;

    while (player->x == -1 && player->y == -1) {
        gettimeofday(&tv, NULL);
        if (map[player->x * player->y] == '0') {
            player->x = tv.tv_sec % MAP_LENGTH;
            player->y = tv.tv_usec % MAP_WIDTH;
            map[MAP_INDEX(player->x, player->y)] = '0' + player->team;
        }    
    }
    ret = play(map, player);
    map[player->x * player->y] = '0' + player->team;
    return (ret);
}
