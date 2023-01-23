/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemipc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:53:43 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/23 16:34:21 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMPIPC_H
# define LEMPIPC_H

# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/msg.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/sem.h>
# include <signal.h>
# include "parsing.h"
# include "debug.h"

# define SHARED_FILE        "shared_memory"
# define MAP_LENGTH         4
# define MAP_WIDTH          4
# define MAP_SIZE           (MAP_LENGTH * MAP_WIDTH)
# define MAP_INDEX(x, y)    (MAP_LENGTH * (y) + (x))

# define EMPTY_TILE '0'

enum game_status {
    not_started,
    in_progress,
    over
};

enum lemipc_status {
    ok,
    ko,
    ended
};

typedef struct  s_ipc_env {
    char    map[MAP_LENGTH * MAP_WIDTH];
    int     msqid;
    int8_t  status;
    int     nb_proc;
    int     sem;
    
}               t_ipc_env;

int     clear_map(void);
int     display_map(char *map);
int     play_game(t_ipc_env *env, t_player *player);
void    *setup_ipc(int *id);

#endif
