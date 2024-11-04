/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:41:46 by hajmoham          #+#    #+#             */
/*   Updated: 2024/11/04 16:43:35 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "Printf/ft_printf.h"
#include "Get_Next_Line/get_next_line.h"
#include "MiniLibX/mlx.h"

typedef struct s_box
{
    int b_map;
    int l_map;
    char **av;
} t_box;