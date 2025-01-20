/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:05:31 by hajmoham          #+#    #+#             */
/*   Updated: 2025/01/18 14:52:01 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	initialize(t_box *map)
{
	int	i;

	i = -1;
	while (++i < 6)
		map->imgs[i] = NULL;
	map->b_map = 0;
	map->l_map = 0;
	map->player = 0;
	map->collectibles = 0;
	map->exit = 0;
	map->exit_x = 0;
	map->exit_y = 0;
	map->dup_collectibles = 0;
	map->dup_exit = 1;
	map->player_x = 0;
	map->player_y = 0;
	map->direction = 0;
	map->moves = 0;
	map->map_store = NULL;
	map->map_dup = NULL;
}

void	get_p_and_e(t_box *map)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (y < map->l_map)
	{
		x = 0;
		while (x < map->b_map)
		{
			if (map->map_dup[y][x] == PLAYER)
			{
				map->player_x = x;
				map->player_y = y;
			}
			if (map->map_dup[y][x] == EXIT)
			{
				map->exit_x = x;
				map->exit_y = y;
				map->map_dup[y][x] = WALL;
			}
			x++;
		}
		y++;
	}
}

void	parcing(t_box *map, char **av)
{
	store_map(av, map);
	if_rectangular(map);
	check_walls(map);
	check_elements(map);
	get_p_and_e(map);
	if (map->player != 1 || map->exit != 1 || map->collectibles < 1)
		error_print("Wrong elements count\n", map);
	map->dup_collectibles = map->collectibles;
	flood_fill(map, map->player_x, map->player_y);
	if (map->dup_collectibles || map->dup_exit)
		error_print("No valid path found\n", map);
}

int	main(int ac, char **av)
{
	t_box	game;

	initialize(&game);
	chk_ber(ac, av, &game);
	check_images(get_images(), &game);
	parcing(&game, av);
	game.mlx = mlx_init();
	game.mlx_win = mlx_new_window(game.mlx, game.b_map * 64, game.l_map * 64, \
	"so_long_bonus");
	create_album(&game);
	rendermap(&game);
	mlx_hook(game.mlx_win, 17, 0, close_game, &game);
	mlx_hook(game.mlx_win, 2, 0, handle_keys, &game);
	mlx_loop(game.mlx);
	cleanup(&game);
	return (0);
}
