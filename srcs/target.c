/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   target.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:20:29 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/24 16:33:36 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

static void send_target(int id, t_player *target, int team) {
    struct mymsg   msg;
    size_t  size = sizeof(t_player);
    int             ret;
    
    memcpy(msg.target, target, sizeof(t_player));
    msg.team = team;
    ret = msgsnd(id, &msg, size, IPC_NOWAIT);
    if (ret >= 0) {
        printf("[SEND] target team %d on (%d, %d)\n", target->team, target->x, target->y);
    }
}

static t_player recv_target(int id, int team) {
    struct mymsg   msg;
    size_t  size = sizeof(t_player);
    int             ret = ok;
    t_player        target;
    
    target.x = -1;
    target.y = -1;
    ret = msgrcv(id, &msg, size, team, IPC_NOWAIT);
    if (ret >= 0) {
        memcpy(&target, msg.target, sizeof(t_player));
        printf("[RECV] target team %d on (%d, %d)\n", target.team, target.x, target.y);
    }
    return (target);
}

static bool  get_target_new_coor(char *map, t_player *target) {
    bool    isfound = false;
    int     neighbors[8] = {MAP_INDEX(target->x, target->y - 1),   // NORTH
                        MAP_INDEX(target->x, target->y + 1),       // SOUTH
                        MAP_INDEX(target->x + 1, target->y),       // EST
                        MAP_INDEX(target->x - 1, target->y),       // OUEST
                        MAP_INDEX(target->x + 1, target->y - 1),   // NORTH-EST
                        MAP_INDEX(target->x - 1, target->y - 1),   // NORTH-OUEST
                        MAP_INDEX(target->x + 1, target->y + 1),   // SUD-EST
                        MAP_INDEX(target->x - 1, target->y + 1)};  // SUD-OUEST

    for (int i = 0; i < 8 && isfound != true; i++) {
        if (neighbors[i] >= 0 && neighbors[i] < MAP_SIZE &&
                map[neighbors[i]] == target->team) {
            *target = index_to_player(neighbors[i]);
        }
    }
    return (isfound);
}

static t_player get_new_target(t_ipc_env *env, t_player *player) {
    t_player    target;

    target.x = -1;    
    target.y = -1;    
    for (int i = MAP_INDEX(player->x, player->y);
            i < MAP_LENGTH * MAP_WIDTH && target.x == -1; i++) {
        if (env->map[i] != player->team + '0' && env->map[i] != '0') {
            target = index_to_player(i);
            target.team = env->map[i] - '0';
        }
    }
    for (int i = MAP_INDEX(player->x, player->y);
            i >= 0 && target.x == -1; i--) {
        if (env->map[i] != player->team + '0' && env->map[i] != '0') {
            target = index_to_player(i);
            target.team = env->map[i] - '0';
        }
    }
    return (target);  
}

t_player    get_target(t_ipc_env *env, t_player *player) {    
    t_player    target;

    target = recv_target(env->msqid, player->team);
    if (target.x == -1) {
        target = get_new_target(env, player);
    }
    else if (env->map[MAP_INDEX(target.x, target.y)] != target.team) {
        if (get_target_new_coor(env->map, &target) == false) {
            target = get_new_target(env, player);
        }
    }
    if (target.x != -1) {
        send_target(env->msqid, &target, player->team);
    }
    return (target);
}
