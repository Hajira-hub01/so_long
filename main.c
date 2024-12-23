/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:05:31 by hajmoham          #+#    #+#             */
/*   Updated: 2024/12/23 15:20:19 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void parcing(t_box *map) 
{
    char **arr = store_map(map->av, map);
    if (if_rectangular(map) == -1 || check_top_bottom_walls(map) == -1 || check_side_walls(map) == -1 || check_elements(map) == -1 || elements_count(map) == -1) 
    {
        free_map_store(map); // Free map_store
        exit(EXIT_FAILURE);
    }
    map_dup(map);
    locate_player(map);
    flood_fill(map, map->player_x, map->player_y);
    if (success_fail(map) == -1) 
    {
        free_map_store(map); // Free map_store
        free_map_dup(map);   // Free map_dup
        exit(EXIT_FAILURE);
    }
    free_map_store(map);
    free_map_dup(map);
}

// void parcing(t_box *map)
// {
//     char **arr;
//     int i;
//     if (!ft_strendcmp(map->av[1], ".ber", 4))
//         error_print("Check Again!! Only '.ber' type files are allowed (-_-)");
//     arr = store_map(map->av, map);
//     if (if_rectangular(map) == -1 || check_top_bottom_walls(map) == -1
//         || check_side_walls(map) == -1 || check_elements(map) == -1 
//         || elements_count(map) == -1)// this one is printing the map if there is an error and freeing the map
//     {
//         i = 0;
//         while (arr[i])
//         {
//             free(arr[i]);
//             i++;
//         }
//         free(arr);
//         exit(EXIT_FAILURE);
//     }
//     map_dup(map);
//     locate_player(map);
//     flood_fill(map, map->player_x, map->player_y);
//     if (success_fail(map) == -1) 
//     {
//         i = 0;
//         while (arr[i]) {
//             printf("lol\n");
//             free(arr[i]);
//             i++;
//         }
//         free(arr);
//         exit(EXIT_FAILURE);
//     }
//     i = 0;
//     while (arr[i]) {
//         // printf("ko\n");
//         printf("%s\n", arr[i]);
//         free(arr[i]);
//         i++;
//     }
//     i = 0;
//     printf("\n");
//     while (map->map_dup[i])
//     {
//         printf("%s\n", map->map_dup[i]);
//         i++;
//     }
    
//     free(arr);
//     free(map->map_dup);
// }

int main(int ac, char **av) 
{
    t_box map;

    if (ac != 2)
        error_print("You need 2 arguments!");
    initialize(&map, ac, av);
    parcing(&map);
    free_map_store(&map);
    free_map_dup(&map);
    return (0);
}
