/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:32:12 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/22 17:27:55 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

bool isdead(char *map, t_player *player) {
    bool isdead = false;
    char neighbors[8] = {map[MAP_INDEX(player->x, player->y - 1)],      // NORTH
                        map[MAP_INDEX(player->x, player->y + 1)],       // SOUTH
                        map[MAP_INDEX(player->x + 1, player->y)],       // EST
                        map[MAP_INDEX(player->x - 1, player->y)],       // OUEST
                        map[MAP_INDEX(player->x + 1, player->y - 1)],   // NORTH-EST
                        map[MAP_INDEX(player->x - 1, player->y - 1)],   // NORTH-OUEST
                        map[MAP_INDEX(player->x + 1, player->y + 1)],   // SUD-EST
                        map[MAP_INDEX(player->x - 1, player->y + 1)]};  // SUD-OUEST

    for (int i = 0; i < 8 && isdead != true; i++) {
        for (int j = i + 1; j < 8 && isdead != true; j++) {
            if (neighbors[i] == neighbors[j]) {
                isdead = true;
            }
        }
    }
    return (isdead);
}

t_player    get_ennemy(char *map, t_player *player) {    
    t_player    ennemy;

    ennemy.x = -1;
    ennemy.y = -1;
    for (int i = MAP_INDEX(player->x, player->y);
            i < MAP_LENGTH * MAP_WIDTH && ennemy.x == -1; i++) {
        if (map[i] != player->team + '0' && map[i] != '0') {
            ennemy.y = i / MAP_WIDTH; 
           if (i != 0) {
                ennemy.x = i % ennemy.y;
            }
            else {
                ennemy.x = 0;
            }
            ennemy.team = map[i] - '0';
        }
    }
    for (int i = MAP_INDEX(player->x, player->y);
            i >= 0 && ennemy.x == -1; i--) {
        if (map[i] != player->team + '0' && map[i] != '0') {
            ennemy.y = i / MAP_WIDTH;
            if (i != 0) {
                ennemy.x = i % ennemy.y;
            }
            else {
                ennemy.x = 0;
            }
            ennemy.team = map[i] - '0';
        }
    }
    return (ennemy);
}

void    move(char *map, t_player *player, t_player *ennemy) {
    t_player tmp;

    tmp = *player;
    if (player->x > ennemy->x &&
            map[MAP_INDEX(player->x - 1, player-> y)] == EMPTY_TILE) {
        --player->x;
    }
    else if (player->x < ennemy->x &&
            map[MAP_INDEX(player->x + 1, player-> y)] == EMPTY_TILE) {
        ++player->x;
    }
    else if (player->y > ennemy->y &&
            map[MAP_INDEX(player->x, player->y - 1)] == EMPTY_TILE) {
        --player->y;
    }
    else if (player->y < ennemy->y &&
            map[MAP_INDEX(player->x, player->y + 1)] == EMPTY_TILE) {
        ++player->y;
    }
    map[MAP_INDEX(tmp.x, tmp.y)] = EMPTY_TILE;
    map[MAP_INDEX(player->x, player->y)] = player->team + '0';
}

