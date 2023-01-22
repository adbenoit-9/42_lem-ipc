/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:08:39 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/22 17:26:14 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include <sys/time.h>
# include <stdbool.h>

# define DEAD 2

# define N  0x80
# define S  0x40
# define E  0x20
# define O  0x10
# define NE 0x08
# define SE 0x04
# define NO 0x02
# define SO 0x01

typedef struct s_player {
    int     x;
    int     y;
    uint8_t team;
    int     msqid;
}   t_player;

bool        isdead(char *map, t_player *player);
t_player    get_ennemy(char *map, t_player *player);
void        move(char *map, t_player *player, t_player *ennemy);

#endif
