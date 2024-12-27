/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:05:31 by hajmoham          #+#    #+#             */
/*   Updated: 2024/12/27 12:24:36 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// void parcing(t_box *map) 
// {
//     char **arr = store_map(av, map);
//     if (if_rectangular(map) == -1 || check_top_bottom_walls(map) == -1 || check_side_walls(map) == -1 || check_elements(map) == -1 || elements_count(map) == -1) 
//     {
//         free_map_store(map); // Free map_store
//         exit(EXIT_FAILURE);
//     }
//     map_dup(map);
//     locate_player(map);
//     flood_fill(map, map->player_x, map->player_y);
//     if (success_fail(map) == -1) 
//     {
//         free_map_store(map); // Free map_store
//         free_map_dup(map);   // Free map_dup
//         exit(EXIT_FAILURE);
//     }
//     free_map_store(map);
//     free_map_dup(map);
// }

void parcing(t_box *map, char **av)
{
	int	i;
	store_map(av, map);
    if_rectangular(map);
    check_walls(map);
    check_side_walls(map);
    check_elements(map);
    if (map->player != 1 || map->exit != 1 || map->collectables < 1)
		error_print("Wrong elements count\n", map);
    map->dup_collectables = map->collectables;
    flood_fill(map, map->player_x, map->player_y);
    if (map->dup_collectables || !map->dup_exit)
		error_print("No valid path found\n", map);
	// printf("map height: %d\n\n", map->l_map);
    // int i = 0;
    // while (map->map_store[i])
    // {
    //     printf("%s\n", map->map_store[i]);
    //     i++;
    // }
	// printf("map height: %d\n", map->l_map);
    // if (!if_rectangular(map) || check_top_bottom_walls(map) == -1
    //     || check_side_walls(map) == -1 || check_elements(map) == -1 
    //     || elements_count(map) == -1)// this one is printing the map if there is an error and freeing the map
    // {
    //     i = 0;
    //     while (arr[i])
    //     {
    //         free(arr[i]);
    //         i++;
    //     }
    //     free(arr);
    //     exit(EXIT_FAILURE);
    // }
    // map_dup(map);
    // locate_player(map);
    // flood_fill(map, map->player_x, map->player_y);
    // if (success_fail(map) == -1) 
    // {
    //     i = 0;
    //     while (arr[i]) {
    //         printf("lol\n");
    //         free(arr[i]);
    //         i++;
    //     }
    //     free(arr);
    //     exit(EXIT_FAILURE);
    // }
    // i = 0;
    // while (arr[i]) {
    //     // printf("ko\n");
    //     printf("%s\n", arr[i]);
    //     free(arr[i]);
    //     i++;
    // }
    // i = 0;
    // printf("\n");
    // while (map->map_dup[i])
    // {
    //     printf("%s\n", map->map_dup[i]);
    //     i++;
    // }
    
    // free(arr);
    // free(map->map_dup);
}

int main(int ac, char **av) 
{
    t_box map;
	
	chk_ber(ac, av, &map);
    initialize(&map);
    parcing(&map, av);
    // so_long();
    free_map_store(&map);
    free_map_dup(&map);
    return (0);
}
