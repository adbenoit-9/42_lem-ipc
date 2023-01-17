/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:32:23 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/17 17:17:45 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

int main(int ac, char **av)
{
    int         ret = 0;
    t_player    player;
    // int8_t  map[MAP_LENGTH * MAP_WIDTH];
    
    if (ac == 1) {
        // ret = display_map();
    }
    else {
        ret = parsing(&av[1], &player);
        if (ret == PARS_OK) {
        }
    }
    return (0);
}
