/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:43:22 by hajmoham          #+#    #+#             */
/*   Updated: 2025/01/18 14:48:25 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/// @brief this is a function that stores the map in the struct
// (map_store and map_dup)
void	store_map(char **av, t_box *map)
{
	int	fd;
	int	i;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		error_print("unable to open the file (;w;)\n", map);
	count_lines(map, av[1]);
	map->map_store = malloc(sizeof(char *) * (map->l_map + 1));
	if (!map->map_store)
		(close(fd), error_print("Malloc Failed\n", map));
	map->map_dup = malloc(sizeof(char *) * (map->l_map + 1));
	if (!map->map_dup)
		(close(fd), error_print("Malloc of dup Failed\n", map));
	i = 0;
	while (i < map->l_map)
	{
		map->map_store[i] = ft_strdup_w_nl(get_next_line(fd));
		map->map_dup[i] = ft_strdup(map->map_store[i]);
		i++;
	}
	map->map_store[i] = NULL;
	map->map_dup[i] = NULL;
	close(fd);
}

void	destroy_images(t_box *map)
{
	if (map->imgs[0])
		mlx_destroy_image(map->mlx, map->imgs[0]);
	if (map->imgs[1])
		mlx_destroy_image(map->mlx, map->imgs[1]);
	if (map->imgs[2])
		mlx_destroy_image(map->mlx, map->imgs[2]);
	if (map->imgs[3])
		mlx_destroy_image(map->mlx, map->imgs[3]);
	if (map->imgs[4])
		mlx_destroy_image(map->mlx, map->imgs[4]);
	if (map->imgs[5])
		mlx_destroy_image(map->mlx, map->imgs[5]);
}

void	cleanup(t_box *map)
{
	int	i;

	destroy_images(map);
	i = -1;
	if (map->map_store)
	{
		while (map->map_store[++i])
			free(map->map_store[i]);
		free(map->map_store);
		map->map_store = NULL;
	}
	i = -1;
	if (map->map_dup)
	{
		while (map->map_dup[++i])
			free(map->map_dup[i]);
		free(map->map_dup);
		map->map_dup = NULL;
	}
}

void	error_print(char *err_txt, t_box *map)
{
	write(2, err_txt, ft_strlen(err_txt));
	cleanup(map);
	exit(EXIT_FAILURE);
}

void	chk_ber(int ac, char **av, t_box *map)
{
	if (ac != 2)
		error_print ("You need 2 arguments!\n", map);
	if (!ft_strendcmp(av[1], ".ber", 4))
		error_print ("Check Again!! Only '.ber' type files are \
		allowed (-_-)\n", map);
}
