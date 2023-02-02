/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:06:06 by adbenoit          #+#    #+#             */
/*   Updated: 2023/02/02 16:37:52 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSG_H
# define MSG_H

# include "player.h"
# include <sys/types.h>

typedef struct	s_msg {
	long int	team;
	char		target[sizeof(t_player)];
}		t_msg;

#endif
