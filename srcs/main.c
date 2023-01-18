/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:32:23 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/18 12:14:26 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

int main(int ac, char **av)
{
    int         ret = LEMIPC_OK;
    int         id;
    t_player    player;
    void        *ptr;
    
    if (ac == 1) {
        // ret = display_map();
    }
    else {
        ret = parsing(&av[1], &player);
        if (ret == PARS_OK) {
            id = shmget(IPC_PRIVATE, MAP_LENGTH * MAP_WIDTH + 1, IPC_CREAT | 0660);
            if (id != -1) {
                ptr = shmat(id, NULL, 0);
                if ((int64_t)ptr == -1) {
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
    }
    return (ret);
}
