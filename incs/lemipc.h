/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemipc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:53:43 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/24 18:13:39 by adbenoit         ###   ########.fr       */
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
# include "msg.h"
# include "debug.h"

# define SHARED_FILE        "shared_memory"
# define MAP_WIDTH         20
# define MAP_HEIGH          20
# define MAP_LENGTH           (MAP_WIDTH * MAP_HEIGH)
# define MAP_INDEX(x, y)    (MAP_WIDTH * (y) + (x))

# define EMPTY_TILE '0'

enum status {
    ok,
    not_started,
    in_progress,
    ko,
    game_over,
    interrupted,
    player_left,
    player_won,
    player_lose
};

typedef struct  s_ipc_env {
    char    map[MAP_LENGTH];
    int     msqid;
    int8_t  status;
    int     nb_proc;
    int     sem;
    
}               t_ipc_env;

int         clear_map(void);
int         display_map(char *map);
int         play_game(t_ipc_env *env, t_player *player);
void        *setup_env(int *id);
t_player    get_target(t_ipc_env *env, t_player *player);
t_player    index_to_player(char *map, int index);
void        clean_env(int id, t_ipc_env *env);
int         game_manager(t_ipc_env *env);

#endif
