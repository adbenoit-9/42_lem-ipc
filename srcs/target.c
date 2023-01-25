/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   target.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:20:29 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/25 19:14:23 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

static void	send_target(int id, t_player *target, int team)
{
	struct mymsg	msg;
	size_t			size = sizeof(t_player);
	int				ret;
	
	memcpy(msg.target, target, sizeof(t_player));
	msg.team = team;
	ret = msgsnd(id, &msg, size, IPC_NOWAIT);
	if (ret >= 0) {
#ifdef DEBUG
		printf("[SEND] Target team %d on (%d, %d)\n", target->team, target->x, target->y);
#endif
	}
}

static t_player	recv_target(int id, int team)
{
	struct mymsg	msg;
	size_t			size = sizeof(t_player);
	int				ret = ok;
	t_player		target;
	
	target.x = -1;
	target.y = -1;
	ret = msgrcv(id, &msg, size, team, IPC_NOWAIT);
	if (ret >= 0) {
		memcpy(&target, msg.target, sizeof(t_player));
#ifdef DEBUG
		printf("[RECV] Target team %d on (%d, %d)\n", target.team, target.x, target.y);
#endif
	}
	return (target);
}

static bool	get_target_new_coor(char *map, t_player *target)
{
	bool	isfound = false;
	int		neighbors[8] = {coor_to_index(target->x, target->y - 1),   // NORTH
						coor_to_index(target->x, target->y + 1),       // SOUTH
						coor_to_index(target->x + 1, target->y),       // EST
						coor_to_index(target->x - 1, target->y),       // OUEST
						coor_to_index(target->x + 1, target->y - 1),   // NORTH-EST
						coor_to_index(target->x - 1, target->y - 1),   // NORTH-OUEST
						coor_to_index(target->x + 1, target->y + 1),   // SUD-EST
						coor_to_index(target->x - 1, target->y + 1)};  // SUD-OUEST

	for (int i = 0; i < 8 && isfound == false; i++) {
		if (neighbors[i] != -1 && map[neighbors[i]] == target->team + '0') {
			*target = index_to_player(map, neighbors[i]);
			isfound = true;
		}
	}
	return (isfound);
}

static t_player	get_new_target(t_ipc_env *env, t_player *player)
{
	t_player	target;

	target.x = -1;    
	target.y = -1;    
	for (int i = coor_to_index(player->x, player->y);
			i < MAP_LENGTH && target.x == -1; i++) {
		if (env->map[i] != player->team + '0' && env->map[i] != '0') {
			target = index_to_player(env->map, i);
			target.team = env->map[i] - '0';
		}
	}
	for (int i = coor_to_index(player->x, player->y);
			i >= 0 && target.x == -1; i--) {
		if (env->map[i] != player->team + '0' && env->map[i] != '0') {
			target = index_to_player(env->map, i);
			target.team = env->map[i] - '0';
		}
	}
	return (target);  
}

t_player	get_target(t_ipc_env *env, t_player *player)
{    
	t_player	target;

	target = recv_target(env->msqid, player->team);
	if (target.x == -1) {
		target = get_new_target(env, player);
	}
	else if (env->map[coor_to_index(target.x, target.y)] != target.team + '0') {
		if (get_target_new_coor(env->map, &target) == false) {
			target = get_new_target(env, player);
		}
	}
	if (target.x != -1) {
		send_target(env->msqid, &target, player->team);
	}
	return (target);
}
