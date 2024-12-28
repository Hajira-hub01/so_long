/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:43:22 by hajmoham          #+#    #+#             */
/*   Updated: 2024/12/28 12:57:06 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void    cleanup(t_box *map)
{
	int	i;

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