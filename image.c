/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:03:44 by hajmoham          #+#    #+#             */
/*   Updated: 2025/01/06 20:07:23 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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