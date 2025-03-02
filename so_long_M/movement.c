/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:59:53 by hajmoham          #+#    #+#             */
/*   Updated: 2025/01/18 13:29:05 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	rendermap(t_box *game)
{
	int	y;
	int	x;

	y = -1;
	while (++y < game->l_map)
	{
		x = -1;
		while (++x < game->b_map)
		{
			if (game->map_store[y][x] == WALL)
				mlx_put_image_to_window(game->mlx, game->mlx_win, \
				game->imgs[1], x * 64, y * 64);
			else
				mlx_put_image_to_window(game->mlx, game->mlx_win, \
				game->imgs[0], x * 64, y * 64);
		}
	}
	render_elements(game);
}

int	close_game(t_box *game)
{
	cleanup(game);
	mlx_destroy_window(game->mlx, game->mlx_win);
	ft_putstr_fd("Game Over!\n", 1);
	exit(0);
	return (0);
}

void	move(int new_x, int new_y, t_box *game)
{
	if (game->map_store[new_y][new_x] == WALL)
		return ;
	if (game->map_store[new_y][new_x] == EXIT && game->collectibles)
		return ;
	if (game->map_store[new_y][new_x] == COIN)
	{
		game->collectibles--;
		mlx_put_image_to_window(game->mlx, game->mlx_win, game->imgs[0], \
		new_x * 64, new_y * 64);
	}
	if (game->map_store[new_y][new_x] == EXIT)
		close_game(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->imgs[0], \
	game->player_x * 64, game->player_y * 64);
	if (!game->direction)
		mlx_put_image_to_window(game->mlx, game->mlx_win, game->imgs[3], \
		new_x * 64, new_y * 64);
	else
		mlx_put_image_to_window(game->mlx, game->mlx_win, game->imgs[2], \
		new_x * 64, new_y * 64);
	game->map_store[game->player_y][game->player_x] = FLOOR;
	game->map_store[new_y][new_x] = PLAYER;
	game->player_x = new_x;
	game->player_y = new_y;
	ft_printf("Moves: %d\n", ++(game->moves));
}

int	handle_keys(int key, t_box *game)
{
	if (key == ESC)
		close_game(game);
	if (key == UP || key == W)
		move(game->player_x, game->player_y - 1, game);
	if (key == DOWN || key == S)
		move(game->player_x, game->player_y + 1, game);
	if (key == RIGHT || key == D)
	{
		game->direction = 1;
		move(game->player_x + 1, game->player_y, game);
	}
	if (key == LEFT || key == A)
	{
		game->direction = 0;
		move(game->player_x - 1, game->player_y, game);
	}
	return (0);
}
