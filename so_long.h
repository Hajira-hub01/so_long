/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:41:46 by hajmoham          #+#    #+#             */
/*   Updated: 2024/11/05 13:26:51 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include "Libft/libft.h"
#include "Printf/ft_printf.h"
#include "Get_Next_Line/get_next_line.h"
#include "MiniLibX/mlx.h"

typedef struct s_box
{
    int b_map;
    int l_map;
    char **map_store;
} t_box;

int count_lines(char *map);
char **store_map(char **av, t_box *map);
void chk_ber (int ac, char **av);
void error_print (char *err_txt);

#endif