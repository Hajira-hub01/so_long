/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:43:22 by hajmoham          #+#    #+#             */
/*   Updated: 2025/01/06 15:10:24 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void    cleanup(t_box *map)
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

void error_print (char *err_txt, t_box *map)
{
    write (2, err_txt, ft_strlen(err_txt));
	cleanup(map);
    exit (EXIT_FAILURE);
}

void chk_ber (int ac, char **av, t_box *map)
{
    if (ac != 2)
        error_print ("You need 2 arguments!\n", map);
    if (!ft_strendcmp(av[1], ".ber", 4))
        error_print ("Check Again!! Only '.ber' type files are allowed (-_-)\n", map);
}

//mlx function that registers key presses
	// it takes:
	// mlx ptr
	// mlx win ptr
	// function | more on later
	// your struct

	// what is the function?

	// every key, has a code, the mlx function recieves that code
	// and sends it to the function you provide to mlx
	// wat does that do?
		// based on what code you recieve, you do a particular action

