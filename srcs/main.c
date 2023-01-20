/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:32:23 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/20 17:47:47 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

int main(int ac, char **av)
{
    int         ret = LEMIPC_OK;
    t_player    player;
    char        *map;
    
    ret = parsing(&av[1], &player);
    if (ret == PARS_OK) {
        map = setup_ipc(&player);
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
            ret = game(map, &player);
        }
    }
    return (ret);
}
