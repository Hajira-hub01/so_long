/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:05:31 by hajmoham          #+#    #+#             */
/*   Updated: 2025/01/06 16:38:43 by hajmoham         ###   ########.fr       */
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

void	create_album(t_box *game)
{
	int	height;
	int	width;
	
	game->imgs[0] = mlx_xpm_file_to_image(game->mlx, "images/floor.xpm", &width, &height);
	if (!game->imgs[0])
		error_print("oops, corrupted image of floor\n", game);
	game->imgs[1] = mlx_xpm_file_to_image(game->mlx, "images/wall.xpm", &width, &height);
	if (!game->imgs[1])
		error_print("oops, corrupted image of wall\n", game);
	game->imgs[2] = mlx_xpm_file_to_image(game->mlx, "images/player_right.xpm", &width, &height);
	if (!game->imgs[2])
		error_print("oops, corrupted image of player_right\n", game);
	game->imgs[3] = mlx_xpm_file_to_image(game->mlx, "images/player_left.xpm", &width, &height);
	if (!game->imgs[3])
		error_print("oops, corrupted image of player_left\n", game);
	game->imgs[4] = mlx_xpm_file_to_image(game->mlx, "images/gem.xpm", &width, &height);
	if (!game->imgs[4])
		error_print("oops, corrupted image of gem\n", game);
	game->imgs[5] = mlx_xpm_file_to_image(game->mlx, "images/exit.xpm", &width, &height);
	if (!game->imgs[5])
		error_print("oops, corrupted image of exit\n", game);
}

void render_elements(t_box *game)
{
	int y = -1;
	int x = -1;
	
	while (++y < game->l_map)
	{
		x = -1;
		while (++x < game->b_map)
		{
			if (game->map_store[y][x] == PLAYER)
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->imgs[3], x * 64, y * 64);
			if (game->map_store[y][x] == COIN)
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->imgs[4], x * 64, y * 64);
			if (game->map_store[y][x] == EXIT)
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->imgs[5], x * 64, y * 64);
		}
	}
}

void	rendermap(t_box *game)
{
	int	y = -1;
	int	x = -1;

	while (++y < game->l_map)
	{
		x = -1;
		while (++x < game->b_map)
		{
			if (game->map_store[y][x] == WALL)
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->imgs[1], x * 64, y * 64);
			else
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->imgs[0], x * 64, y * 64);
		}
	}
	render_elements(game);
}

char **get_images()
{
	static char *str_img[7] = {
		"images/floor.xpm",
		"images/wall.xpm",
		"images/player_right.xpm",
		"images/player_left.xpm",
		"images/gem.xpm",
		"images/exit.xpm", NULL
		};
	return (str_img);
}

void	check_images(char **imgs, t_box *game)
{
	int	i;
	int	fd;
	
	i = 0;
	while (imgs[i])
	{
		fd = open(imgs[i], O_RDONLY);
		if (fd == -1)
			error_print("couldn't access image\n", game);
		close (fd);
		i++;
	}
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
		return;
	if (game->map_store[new_y][new_x] == COIN)
	{
		game->collectables--;
		mlx_put_image_to_window(game->mlx, game->mlx_win, game->imgs[0], new_x * 64, new_y * 64);
	}
	if (game->map_store[new_y][new_x] == EXIT)
		if (!game->collectables)
			close_game(game);// close game
	// more things to consider for exit
	// check direction (L/R) to paste the image 
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->imgs[0], game->player_x * 64, game->player_y * 64);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->imgs[3], new_x * 64, new_y * 64);
	game->player_x = new_x;
	game->player_y = new_y;
	// print moves count
}

int	handle_keys(int key, t_box *game)
{
	if (key == ESC)
		close_game(game);// close game
	if (key == UP || key == W)
		move(game->player_x, game->player_y - 1, game);// moves up
	if (key == DOWN || key == S)
		move(game->player_x, game->player_y + 1, game);// moves down
	if (key == RIGHT || key == D)
		move(game->player_x + 1, game->player_y, game);// moves right
	if (key == LEFT || key == A)
		move(game->player_x - 1, game->player_y, game);// moves left
	return (0);
}

int main(int ac, char **av) 
{
    t_box game;
	
    initialize(&game);
	chk_ber(ac, av, &game);
	check_images(get_images(), &game);
    parcing(&game, av);

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
