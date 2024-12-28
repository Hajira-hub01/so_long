/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:05:31 by hajmoham          #+#    #+#             */
/*   Updated: 2024/12/28 13:38:16 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize(t_box *map)
{
	map->b_map = 0;
	map->l_map = 0;
	map->player = 0;
	map->collectables = 0;
	map->exit = 0;
	map->dup_collectables = 0;
	map->dup_exit = 1;
	map->player_x = 0;
	map->player_y = 0;
	map->map_store = NULL;
	map->map_dup = NULL;
}

void parcing(t_box *map, char **av)
{
	store_map(av, map);
    if_rectangular(map);
    check_walls(map);
    check_elements(map);
    if (map->player != 1 || map->exit != 1 || map->collectables < 1)
		error_print("Wrong elements count\n", map);
    map->dup_collectables = map->collectables;
    flood_fill(map, map->player_x, map->player_y);
    if (map->dup_collectables || map->dup_exit)
		error_print("No valid path found\n", map);
}

int main(int ac, char **av) 
{
    t_box map;
	
    initialize(&map);
	chk_ber(ac, av, &map);
    parcing(&map, av);
	error_print("No errors, we passed the parsing!\n", &map);
    // so_long();
    return (0);
}
