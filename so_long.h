/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:41:46 by hajmoham          #+#    #+#             */
/*   Updated: 2024/12/23 15:17:46 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include "Libft/libft.h"
#include "Printf/ft_printf.h"
#include "Get_Next_Line/get_next_line.h"
#include "MiniLibX/mlx.h"
#include <stdint.h>

typedef struct s_box
{
    int ac;
    char **av;
    char **map_store;
    char **map_dup;
    int b_map;
    int l_map;
    int player;
    int collectables;
    int dup_collectables;
    int exit;
    int player_x;
    int player_y;
    int reachable_c;
    int reachable_e;
} t_box;

void initialize(t_box *map, int ac, char **av);
int count_lines(char *map);
char **store_map(char **av, t_box *map);
void chk_ber (int ac, char **av);
void error_print (char *err_txt);
int	check_elements(t_box *map);
int	check_side_walls(t_box *map);
int	check_top_bottom_walls(t_box *map);
int	if_rectangular(t_box *map);
int	elements_count(t_box *map);
char **map_dup(t_box *map);
int locate_player(t_box *map);
void	flood_fill(t_box *map, int x, int y);
int	valid_map(t_box *map);
int success_fail(t_box *map);
void free_map_store(t_box *map);
void free_map_dup(t_box *map);
void parcing(t_box *map);

#endif