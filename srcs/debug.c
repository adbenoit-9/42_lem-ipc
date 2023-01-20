/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:12:02 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/20 16:42:52 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void    print_player(const char *file, int line, t_player *player) {
    printf("\033[33m%s l.%d:\033[0m PLAYER (%d, %d) - team %d - map index %d\n",
            file, line, player->x, player->y, player->team,
            MAP_INDEX(player->x, player->y));
}
