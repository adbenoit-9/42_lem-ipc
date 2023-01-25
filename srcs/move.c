/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:14:26 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/25 18:45:52 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

static void better_move_x(char *map, t_player *player, int dir_x, int dir_y) {
    if (map[coor_to_index(player->x + dir_x, player->y)] == EMPTY_TILE) {
        player->x += dir_x;
    }
    else if (map[coor_to_index(player->x, player->y + dir_y)] == EMPTY_TILE) {   
        player->y += dir_y;
    }
    else if (coor_to_index(player->x, player->y - dir_y) != -1 &&
        map[coor_to_index(player->x, player->y - dir_y)] == EMPTY_TILE) {
        player->y -= dir_y; 
    }
    else if (coor_to_index(player->x, player->x - dir_x) != -1 &&
        map[coor_to_index(player->x, player->x - dir_x)] == EMPTY_TILE) {
        player->x -= dir_x; 
    }
}

static void better_move_y(char *map, t_player *player, int dir_x, int dir_y) {
    if (map[coor_to_index(player->x, player->y + dir_y)] == EMPTY_TILE) {   
        player->y += dir_y; 
    }
    else if (map[coor_to_index(player->x + dir_x, player->y)] == EMPTY_TILE) {
        player->x += dir_x; 
    }
    else if (coor_to_index(player->x - dir_x, player->y) != -1 &&
        map[coor_to_index(player->x - dir_x, player->y)] == EMPTY_TILE) {
        player->x -= dir_x; 
    }
    else if (coor_to_index(player->x, player->y - dir_y) != -1 &&
        map[coor_to_index(player->x, player->y - dir_y)] == EMPTY_TILE) {
        player->y -= dir_y; 
    }
}

void    move(char *map, t_player *player, t_player *target) {
    t_player tmp;
    int     dist[2];
    int     dir[2];

    tmp = *player;
    dist[0] = abs(player->x - target->x);
    dist[1] = abs(player->y - target->y);
    dir[0] = player->x > target->x ? -1 : (player->x < target->x ? 1 : 0);
    dir[1] = player->y > target->y ? -1 : (player->y < target->y ? 1 : 0);
    if (dist[0] > 1 || dist[1] > 1) {
        if (dist[0] > dist[1] || (dist[0] == dist[1] && rand() % 1 == 1)) {
            better_move_x(map, player, dir[0], dir[1]);
        }
        else {
            better_move_y(map, player, dir[0], dir[1]);
        }
    }
    map[coor_to_index(tmp.x, tmp.y)] = EMPTY_TILE;
    map[coor_to_index(player->x, player->y)] = player->team + '0';
}
