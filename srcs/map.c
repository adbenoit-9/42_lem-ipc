/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:29:07 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/25 19:09:47 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

int	clear_map(void)
{
	int		n = MAP_HEIGH;
	char	erase[8 * n];

	for (int i = 0; i < n; i++) {
		strncpy(&erase[i * 8], "\033[A\033[2K", 8);
	}
	write(STDOUT_FILENO, erase, 8 * n);
	return (ok);
}

int	display_map(char *map)
{
	char	dmap[(MAP_WIDTH + 1) * MAP_HEIGH + 1];
	int		j = 0;

	dmap[0] = 0;
	for (int i = 0; i < MAP_HEIGH; i++) {
		strncat(dmap, &map[j], MAP_WIDTH);
		j += MAP_WIDTH;
		dmap[j + i] = '\n';
		dmap[j + i + 1] = 0;
	}
	write(STDOUT_FILENO, dmap, (MAP_WIDTH + 1) * MAP_HEIGH);
	return (ok);
}
