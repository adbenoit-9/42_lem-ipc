/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:06:06 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/25 19:17:17 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSG_H
# define MSG_H

# include "player.h"
# include <sys/types.h>

typedef struct	mymsg {
	long int	team;
	char		target[sizeof(t_player)];    
}				t_msg;

#endif
