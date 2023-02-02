/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:08:39 by adbenoit          #+#    #+#             */
/*   Updated: 2023/02/02 16:36:56 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include <sys/time.h>
# include <stdbool.h>

typedef struct	s_player {
	int	x;
	int	y;
	uint8_t	team;
}		t_player;

#endif
