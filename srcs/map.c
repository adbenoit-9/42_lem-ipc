/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:29:07 by adbenoit          #+#    #+#             */
/*   Updated: 2023/01/22 16:52:21 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

int clear_map(void) {
    int n = MAP_LENGTH;
    char erase[8 * n];

    for (int i = 0; i < n; i++) {
        strncpy(&erase[i * 8], "\033[A\033[2K", 8);
    }
    write(STDOUT_FILENO, erase, 8 * n);
    return (LEMIPC_OK);
}

int display_map(char *map) {
    char dmap[(MAP_LENGTH + 1) * MAP_WIDTH + 1];
    int j = 0;

    dmap[0] = 0;
    for (int i = 0; i < MAP_WIDTH; i++) {
        strncat(dmap, &map[j], MAP_LENGTH);
        j += MAP_LENGTH;
        dmap[j + i] = '\n';
        dmap[j + i + 1] = 0;
    }
    write(STDOUT_FILENO, dmap, (MAP_LENGTH + 1) * MAP_WIDTH);
    sleep(1);
    clear_map();
    return (LEMIPC_OK);
}
