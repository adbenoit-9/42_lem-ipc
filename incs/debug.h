/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 01:38:31 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/26 01:39:07 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# ifdef LOG
#  define PRINT_LOG(color, type, str, team, x, y)	do {\
				printf("%s[%s] %s team %d at (%d, %d)\033[0m\n", color, type, str, team, x, y);\
				} while (0);
# else
#  define PRINT_LOG(color, type, str, team, x, y)
# endif

# ifdef DEBUG
#  define PRINT_DEBUG(str)	do { printf("%s\n", str); } while (0);
# else
#  define PRINT_DEBUG(str)
# endif

#endif
