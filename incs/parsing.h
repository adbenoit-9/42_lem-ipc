/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:52:35 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/17 17:08:32 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <stdint.h>
# include <stdlib.h>
# include "player.h"

# define NB_FLAG	2

# define PARS_STOP	-1
# define PARS_OK	0
# define E_BADARG	1
# define E_NODARG	2
# define E_BADTEAM	3

# define EM_BADARG	"lemipc: invalid argument: \'%s\'\n"
# define EM_NOARG	"lemipc: option requires an argument -- \'%s\'\n"
# define EM_BADTEAM	"lemipc:  invalid argument: \'%s\': 0 <= value <= %d\n"

# define MAX_TEAM	(uint8_t)150

int parsing(char **av, t_player *player);

#endif
