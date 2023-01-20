/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:12:02 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/20 16:21:58 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void    print_player(t_player *player) {
    printf("\033[33mPLAYER (%d, %d) - team %d - map index %d\033[0m\n", player->x,
            player->y, player->team, MAP_INDEX(player->x, player->y));
}
