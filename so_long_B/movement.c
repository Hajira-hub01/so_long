/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:59:53 by hajmoham          #+#    #+#             */
/*   Updated: 2025/01/20 10:41:04 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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
	display_moves(game);
}

int	close_game(t_box *game)
{
	cleanup(game);
	mlx_destroy_window(game->mlx, game->mlx_win);
	ft_putstr_fd("Game Over!\n", 1);
	exit(0);
	return (0);
}

void	display_moves(t_box *game)
{
	char	*move_count;
	char	*value;

	value = ft_itoa(game->moves);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->imgs[1], 0, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->imgs[1], 64, 0);
	move_count = ft_strjoin("Moves: ", value);
	mlx_string_put(game->mlx, game->mlx_win, 10, 10, 0x000000, move_count);
	free(value);
	free(move_count);
}

void	move(int new_x, int new_y, t_box *game)
{
	if ((game->map_store[new_y][new_x] == WALL)
		|| (game->map_store[new_y][new_x] == EXIT && game->collectibles))
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
	game->moves++;
	display_moves(game);
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
