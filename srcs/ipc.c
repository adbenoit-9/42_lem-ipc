/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:45:28 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/22 17:30:07 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "lemipc.h"

void    *init_env(key_t key, t_ipc_env *env) {
    memset(env->map, '0', MAP_LENGTH * MAP_WIDTH);
    env->status = GAME_NOT_STARTED;
    env->nb_proc = 1;
    env->msqid = msgget(key, IPC_CREAT);
    if (env->msqid == -1) {
        perror("msgget");
        env = (void *)-1;
    }
    return (env);
}

void    *setup_ipc(int *id)
{
    t_ipc_env   *ptr = 0;
    int         isset = 0;
    key_t       key;
    
    key = ftok("shared_mem", 1);
    *id = shmget(key, sizeof(t_ipc_env), IPC_CREAT | IPC_EXCL | 0660);
    if (errno == EEXIST) {
        isset = 1;
        *id = shmget(key, sizeof(t_ipc_env), 0660);
    }
    else if (*id == -1) {
        perror("shmget");
        ptr = (void *)-1;
    }
    if (*id != -1) {
        ptr = shmat(*id, NULL, 0);
        if ((int64_t)ptr == -1) {
            perror("shmat");
        }
        else if (isset == 0) {
            ptr = init_env(key, ptr);
        }
        else  {
            ++ptr->nb_proc;
        }
    }
    return (ptr);    
}
