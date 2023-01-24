/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:32:23 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/24 18:15:22 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

int     g_signal_catch = 0;

void    handle_signal(int signal)
{
    if (signal == SIGINT) {
        g_signal_catch = 1;
    }
}

static void print_status(int status) {
    char    *str[] = {
        "\033[33;1m[QUIT] Game interrupted.\033[0m",
        "\033[33;1m[QUIT] You left the game.\033[0m",
        "\033[32;1m[GAME OVER] Congratulations, you won the game !\033[0m",
        "\033[31;1m[GAME OVER] You lose the game.\33[0m"
    };
    for (int i = 0; i < 4; i++) {
        if (status == i + interrupted){
            printf("%s\n", str[i]);
        }
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
        env = setup_env(&id);
        if ((int64_t)env == -1) {
            ret = ko;
        }
        else {
            while (ret < ko) {
                if (semop(env->sem, &sem_lock, 1) == -1) {
                    perror("semop");
                }
                if (ac == 1) {
                    ret = game_manager(env);
                    if (g_signal_catch == 1) {
                        env->status = interrupted;
                        ret = interrupted;
                    }
                }
                else {
                    if (g_signal_catch == 1 && player.x != -1) {
                        env->map[MAP_INDEX(player.x, player.y)] = EMPTY_TILE;
                        ret = player_left;
                    }
                    else {
                        ret = play_game(env, &player);
                    }
                }
                semop(env->sem, &sem_unlock, 1);
            }
            print_status(ret);
            ret = ok;
            clean_env(id, env);
        }
    }
    return (ret);
}
