/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:32:23 by adbenoit          #+#    #+#             */
/*   Updated: 2023/02/02 16:42:40 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

static int	g_signal_catch = 0;

static void	handle_signal(int signal)
{
	(void)signal;
	g_signal_catch = 1;
}

static void	print_status(int status)
{
	static char	*str[] = {
		"\033[33;1m[QUIT] Game interrupted.\033[0m",
		"\033[33;1m[QUIT] You left the game.\033[0m",
		"\033[32;1m[GAME OVER] Congratulations, you won the game !\033[0m",
		"\033[31;1m[GAME OVER] You lose the game.\33[0m"
		};

	if (status >= interrupted) {
		printf("%s\n", str[status - interrupted]);
	}
}

static int	lemipc(t_ipc_env *env, t_player *player)
{
	int		ret = ok;
	struct sembuf	sem_lock = {0, -1 , SEM_UNDO};
	struct sembuf	sem_unlock = {0, 1 , SEM_UNDO};

	ret = semop(env->sem, &sem_lock, 1);
	if (ret == -1) {
		if (errno == EINTR) {
			PRINT_DEBUG("[WARNING] semop: Interrupted system call");
		}
		else {
			ret = ko;
			perror("semop");
		}
	}
	else if (player->team == 0) {
		ret = game_manager(env);
		if (g_signal_catch == 1) {
			env->status = interrupted;
			ret = interrupted;
		}
		semop(env->sem, &sem_unlock, 1);
	}
	else {
		if (g_signal_catch == 1 && player->x != -1) {
			env->map[coor_to_index(player->x, player->y)] = EMPTY_TILE;
			ret = player_left;
		}
		else {
			ret = play_game(env, player);
		}
		semop(env->sem, &sem_unlock, 1);
	}
	return (ret);
}

int	main(int ac, char **av)
{
	int		ret = ok;
	t_player	player;
	t_ipc_env	*env;
	int		id = 0;

	(void)ac;
	ret = parsing(&av[1], &player);
	if (ret == PARS_OK) {
		signal(SIGINT, &handle_signal);
		signal(SIGTERM, &handle_signal);
		signal(SIGQUIT, &handle_signal);
		env = setup_env(&id);
		if ((int64_t)env == -1) {
			ret = ko;
		}
		else {
			while (ret < ko) {
				ret = lemipc(env, &player);
				if (ret < ko && (player.x != -1 || player.team == 0)) {
					sleep(1);
				}
			}
			print_status(ret);
			ret = ok;
			clean_env(id, env);
		}
	}
	ret = ret == PARS_STOP ? ok : ret;
	return (ret);
}
