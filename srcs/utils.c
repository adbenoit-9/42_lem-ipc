/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:13:37 by adbenoit          #+#    #+#             */
/*   Updated: 2023/02/02 16:33:04 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

t_player	index_to_player(char *map, int index)
{
	t_player	player;

	player.y = index / MAP_WIDTH;
	player.x = index % MAP_WIDTH;
	player.team = map[index] - '0';
	return (player);
}

int	coor_to_index(int x, int y)
{
	int	index;

	if (x < 0 || y < 0 || x >= MAP_WIDTH || y >= MAP_HEIGH) {
		index = -1;
	}
	else {
		index = MAP_WIDTH * y + x;
	}
	return (index);
}
