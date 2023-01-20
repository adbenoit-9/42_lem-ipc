/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:45:28 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/20 17:50:23 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "lemipc.h"

void    *setup_ipc(t_player *player)
{
    void        *ptr = 0;
    int         id;
    int         isset = 0;
    key_t       key;
    
    key = ftok("shared_mem", 1);
    player->msqid = msgget(key, IPC_CREAT);
    if (player->msqid == -1) {
        perror("msgget");
        ptr = (void *)-1;
    }
    id = shmget(key, MAP_LENGTH * MAP_WIDTH, IPC_CREAT | IPC_EXCL | 0660);
    if (errno == EEXIST) {
        isset = 1;
        id = shmget(key, MAP_LENGTH * MAP_WIDTH, 0660);
    }
    else if (id == -1)
     {
        perror("shmget");
        ptr = (void *)-1;
    }
    if (id != -1) {
        ptr = shmat(id, NULL, 0);
        if ((int64_t)ptr == -1) {
            perror("shmat");
        }
        else if (isset == 0) {
            memset((char *)ptr, '0', MAP_LENGTH * MAP_WIDTH);
        }
    }
    return (ptr);    
}
