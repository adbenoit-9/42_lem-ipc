/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:32:23 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/23 18:21:21 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

int     g_signal_catch = 0;

void    handle_signal(int signal)
{
    if (signal == SIGINT) {
        g_signal_catch = 1;
        printf("Quit.\n");
    }
}

int game_manager(t_ipc_env *env) {
    char    team = 0;
    int     ret = ok;
    int     count_team = 0;
    
    display_map(env->map);
    if (env->status == not_started) {
        env->status = in_progress;
    }
    for (int i = 0; i < MAP_LENGTH * MAP_WIDTH && count_team < 2; i++) {
        if (env->map[i] != EMPTY_TILE && env->map[i] != team) {
            team = env->map[i];
            ++count_team;
        }
    }
    if (count_team == 1) {
        env->status = over;
        printf("Team %c won !\n", team);
        ret = ended;
    }
    else {
        sleep(1);
        clear_map();
    }
    return (ret);
}

void    clean_env(int id, t_ipc_env *env) {
    struct sembuf sem_lock = {0, -1 , SEM_UNDO};
    struct sembuf sem_unlock = {0, 1 , SEM_UNDO};
    
    semop(env->sem, &sem_lock, 1);
    --env->nb_proc;
    if (env->nb_proc == 0) {
        semop(env->sem, &sem_unlock, 1);
        semctl(env->sem, 0, IPC_RMID);
        shmdt(env);
        shmctl(id, IPC_RMID, 0);
    }
    else {
        semop(env->sem, &sem_unlock, 1);
        shmdt(env);
#ifdef DEBUG
        printf("clean\n");
#endif
    }
}

int main(int ac, char **av)
{
    int         ret = ok;
    t_player    player;
    t_ipc_env   *env;
    int         id = 0;
    struct sembuf sem_lock = {0, -1 , SEM_UNDO};
    struct sembuf sem_unlock = {0, 1 , SEM_UNDO};
    
    
    ret = parsing(&av[1], &player);
    signal(SIGINT, &handle_signal);
    if (ret == PARS_OK) {
        env = setup_ipc(&id);
        if ((int64_t)env == -1) {
            ret = ko;
        }
        else {
            while (ret != ended && g_signal_catch == 0) {
                if (semop(env->sem, &sem_lock, 1) == -1) {
                    perror("semop");
                }
                if (ac == 1) {
                    ret = game_manager(env);
                }
                else {
                    if (g_signal_catch == 1 && player.x != -1) {
                        env->map[MAP_INDEX(player.x, player.y)] = EMPTY_TILE;
                    }
                    else {
                        ret = play_game(env, &player);
                    }
                }
                if (env->status == over) {
                    ret = ended;
                }
                semop(env->sem, &sem_unlock, 1);
            }
            ret = ok;
            clean_env(id, env);
        }
    }
    return (ret);
}
