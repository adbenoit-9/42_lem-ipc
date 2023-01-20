/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:32:23 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/20 12:40:19 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

int main(int ac, char **av)
{
    int         ret = LEMIPC_OK;
    int         id;
    key_t       key;
    t_player    player;
    void        *map;
    
    ret = parsing(&av[1], &player);
    if (ret == PARS_OK) {
        key = ftok("shared_mem", 1);
        id = shmget(key, MAP_LENGTH * MAP_WIDTH, IPC_CREAT | IPC_EXCL | 0660);
        printf("errno: %d\nid: %d\n", errno, id);
        if (id != -1) {
            map = shmat(id, NULL, 0);
            memset((char *)map, '1', MAP_LENGTH * MAP_WIDTH);
            printf("map ptr: %p\n", map);
            if ((int64_t)map == -1) {
                perror("shmat");
                ret = LEMIPC_KO;
            }
        }
        else if (errno == EEXIST) {
            id = shmget(key, MAP_LENGTH * MAP_WIDTH, 0660);
            map = shmat(id, NULL, 0);
            if ((int64_t)map == -1) {
                perror("shmat");
                ret = LEMIPC_KO;
            }
        }
        else {
            perror("shmget");
            ret = LEMIPC_KO;
        }
    }
    else {
        ret = LEMIPC_KO;
    }
    while (ret == LEMIPC_OK) {
        if (ac == 1) {
            sleep(1);
            ret = display_map(map);
        }
        else {
        }
    }
    return (ret);
}
