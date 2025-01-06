/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:05:31 by hajmoham          #+#    #+#             */
/*   Updated: 2025/01/06 20:14:11 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
# define LADY	"Hajira"
# define BOY	"Tarek"

void	initialize(t_box *map)
{
	// dont forget to remove these ^-^
	int	i;

	i = -1;
	while (++i < 6)
		map->imgs[i] = NULL;
	map->b_map = 0;
	map->l_map = 0;
	map->player = 0;
	map->collectables = 0;
	map->exit = 0;
	map->dup_collectables = 0;
	map->dup_exit = 1;
	map->player_x = 0;
	map->player_y = 0;
	map->direction = 0;
	map->moves = 0;
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
    t_box game;
	
    initialize(&game);
	chk_ber(ac, av, &game);
	check_images(get_images(), &game);
    parcing(&game, av);

	// direction flag

	// solve exit problem

	// game section
	game.mlx = mlx_init();
	game.mlx_win = mlx_new_window(game.mlx, game.b_map * 64, game.l_map * 64, "so_long");
	create_album(&game);
	rendermap(&game);
	mlx_hook(game.mlx_win, 17, 0, close_game, &game);
	mlx_hook(game.mlx_win, 2, 0, handle_keys, &game);
	mlx_loop(game.mlx);
	cleanup(&game);
    return (0);
}