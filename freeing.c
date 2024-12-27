/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 10:33:02 by hajmoham          #+#    #+#             */
/*   Updated: 2024/12/25 10:33:13 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void free_map_store(t_box *map) 
{
    int i = 0;

    while (map->map_store[i]) 
    {
        free(map->map_store[i]); // Free each row
        i++;
    }
    free(map->map_store); // Free the array itself
    map->map_store = NULL;
}

void free_map_dup(t_box *map) 
{
    int i = 0;

    while (map->map_dup[i]) 
    {
        free(map->map_dup[i]); // Free each row
        i++;
    }
    free(map->map_dup); // Free the array itself
    map->map_dup = NULL;
}

