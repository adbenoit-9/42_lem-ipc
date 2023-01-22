/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:32:23 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/22 17:33:00 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

void    handle_signal(int signal)
{
    if (signal == SIGINT) {
        printf("You can't quit the game.\n");
    }
}

int handle_game(t_ipc_env *env) {
    display_map(env->map);
    if (env->status == GAME_NOT_STARTED) {
        env->status = GAME_IN_PROGRESS;
    }
    else if (env->status == GAME_IN_PROGRESS) {
        int count_team = 0;
        for (int i = 0; i < MAP_LENGTH * MAP_WIDTH && count_team < 2; i++) {
            if (env->map[i] != EMPTY_TILE) {
                ++count_team;
            }
        }
        if (count_team < 2) {
            env->status = GAME_OVER;
        }
    }
    return (LEMIPC_OK);
}

void    clean_env(int id, t_ipc_env *env) {
    --env->nb_proc;
    if (env->nb_proc == 0) {
        shmdt(env);
        shmctl(id, IPC_RMID, 0);
    }
    else {
        shmdt(env);
    }
}

int main(int ac, char **av)
{
    int         ret = LEMIPC_OK;
    t_player    player;
    t_ipc_env   *env;
    int         id = 0;
    
    ret = parsing(&av[1], &player);
    // if (ac > 1) {
    //     signal(SIGINT, &handle_signal);
    // }
    if (ret == PARS_OK) {
        env = setup_ipc(&id);
        if ((int64_t)env == -1) {
            ret = LEMIPC_KO;
        }
        else {
            while (env->status != GAME_OVER) {
                if (ac == 1) {
                    handle_game(env);
                }
                else {
                    play_game(env, &player);
                }
            }
            clean_env(id, env);
        }
    }
    return (ret);
}
