/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:52:08 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/22 16:58:39 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void    print_error(int err, char *str) {
    char *err_mess[] = {
            EM_BADARG,
            EM_NOARG,
            EM_BADTEAM};
    
    if (err == E_BADTEAM) {
        dprintf(STDERR_FILENO, err_mess[err - 1], str, MAX_TEAM);
    }
    else {
        dprintf(STDERR_FILENO, err_mess[err - 1], str);
    }
}

int set_team(char *team, t_player *player) {
    int     ret = PARS_OK;
    int16_t  team_id;
    
    if (team == NULL) {
        ret = E_NODARG;
    }
    else {
        for (int i = 0; team[i] && ret == PARS_OK; i++) {
            if (!isdigit(team[i])) {
                ret = E_BADTEAM;
            }
        }
    }
    if (ret == PARS_OK) {
        team_id = atoi(team);
        if (team_id < 0 || team_id > MAX_TEAM) {
            ret = E_BADTEAM;
        }
        else {
            player->team = (uint8_t)team_id;
            player->x = -1;
            player->y = -1;
        }
    }
    return (ret);
}

int print_help(char *str, t_player *player) {
    (void)str;
    (void)player;
    printf("Usage\n./lemipc [options]\n\nOptions\n");
    printf("--help         print help and exit\n");
    printf("--team         define the team of the player (must be a number between 0 and 150)\n");
    return (PARS_STOP);
}

int parsing(char **av, t_player *player) {
    int     ret = PARS_OK;
    int     i;
	int	    (*flags_handler[])(char *, t_player *) = {
						set_team, print_help};
	char    *flag_list[] = {"--team", "--help"};
    
    for (i = 0; av[i] && ret == PARS_OK; i++) {
        ret = E_BADARG;
        for (int j = 0; j != NB_FLAG && ret == E_BADARG; j++) {
            if (strcmp(av[i], flag_list[j]) == 0) {
                ++i;
                ret = flags_handler[j](av[i], player);
            }
        }
    }
    ret = ret == PARS_STOP ? PARS_OK : ret;
    if (ret != PARS_OK) {
        if (ret == E_NODARG) {
            print_error(ret, &av[i - 2][2]);
        }
        else {
            print_error(ret, av[i - 1]);
        }
    }
    return (ret);    
}
