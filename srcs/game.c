/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:13:16 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/24 18:13:29 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

int game_manager(t_ipc_env *env) {
    char    team = 0;
    int     ret = ok;
    int     count_team = 0;
    
    display_map(env->map);
    if (env->status == not_started) {
        env->status = in_progress;
    }
    for (int i = 0; i < MAP_LENGTH && count_team < 2; i++) {
        if (env->map[i] != EMPTY_TILE && env->map[i] != team) {
            team = env->map[i];
            ++count_team;
        }
    }
    if (count_team == 1) {
        env->status = game_over;
        ret = game_over;
        printf("\033[33;1m[GAME OVER] Team %c won !\033[0m\n", team);
    }
    else {
        sleep(1);
        clear_map();
    }
    return (ret);
}
