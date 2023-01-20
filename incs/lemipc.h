/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemipc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:53:43 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/20 16:29:05 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMPIPC_H
# define LEMPIPC_H

# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/msg.h>
# include <errno.h>
# include "parsing.h"
# include "debug.h"

# define MAP_LENGTH 4
# define MAP_WIDTH  4
# define MAP_INDEX(x, y)    (MAP_LENGTH * (y) + (x))

# define EMPTY_TILE 0
# define LEMIPC_OK 0
# define LEMIPC_KO 1

int clear_map(void);
int display_map(char *map);
int lemipc(char *map, t_player *player);

#endif
