/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:32:23 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/22 13:11:34 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

void    handle_signal(int signal)
{
    if (signal == SIGINT) {
        printf("You can't quit the game.\n");
    }
}

int main(int ac, char **av)
{
    int         ret = LEMIPC_OK;
    t_player    player;
    char        *map;
    
    ret = parsing(&av[1], &player);
    // if (ac > 1) {
    //     signal(SIGINT, &handle_signal);
    // }
    if (ret == PARS_OK) {
        map = setup_ipc(&player);
        if ((int64_t)map ==-1) {
            ret = LEMIPC_KO;
        }
    }
    else {
        ret = LEMIPC_KO;
    }
    while (ret == LEMIPC_OK && map[STATUS_INDEX] != GAME_OVER) {
        if (ac == 1) {
            ret = display_map(map);
            if (map[STATUS_INDEX] == GAME_NOT_STARTED) {
                map[STATUS_INDEX] = GAME_IN_PROGRESS;
            }
            else if (map[STATUS_INDEX] == GAME_IN_PROGRESS) {
                int count_team = 0;
                for (int i = 0; i < MAP_LENGTH * MAP_WIDTH && count_team < 2; i++) {
                    if (map[i] != EMPTY_TILE) {
                        ++count_team;
                    }
                }
                if (count_team < 2) {
                    map[STATUS_INDEX] = GAME_OVER;
                }
            }
        }
        else {
            ret = game(map, &player);
        }
    }
    return (ret);
}
