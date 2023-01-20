/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:32:23 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/20 14:00:05 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

void    *get_shared_mem()
{
    void        *ptr = 0;
    int         id;
    int         isset = 0;
    key_t       key;
    
    key = ftok("shared_mem", 1);
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

int main(int ac, char **av)
{
    int         ret = LEMIPC_OK;
    t_player    player;
    char        *map;
    
    ret = parsing(&av[1], &player);
    if (ret == PARS_OK) {
        map = get_shared_mem();
        if ((int64_t)map ==-1) {
            ret = LEMIPC_KO;
        }
    }
    else {
        ret = LEMIPC_KO;
    }
    while (ret == LEMIPC_OK) {
        if (ac == 1) {
            ret = display_map(map);
        }
        else {
            ret = lemipc(map, &player);
        }
    }
    return (ret);
}
