/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:41:46 by hajmoham          #+#    #+#             */
/*   Updated: 2025/01/06 15:42:19 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define WALL   '1'
# define FLOOR  '0'
# define COIN   'C'
# define EXIT   'E'
# define PLAYER 'P'

#include "Libft/libft.h"
#include "Printf/ft_printf.h"
#include "Get_Next_Line/get_next_line.h"
#include "mlx/mlx.h"
#include <stdint.h>

typedef enum keys
{
	UP = 126,
	DOWN = 125,
	RIGHT = 124,
	LEFT = 123,
	W = 13,
	A = 0,
	S = 1,
	D = 2,
	ESC = 53
}	t_keys;

typedef struct s_box
{
	void		*mlx;
	void		*mlx_win;
	void		*imgs[6];
    char		**map_store; //free both at end
    char		**map_dup; //free both at end
    int			b_map;
    int			l_map;
    int			player;
    int			collectables;
    int			dup_collectables;
    int			exit;
    int			dup_exit;
    int			player_x;
    int			player_y;
}	t_box;

void    initialize(t_box *map);
void    count_lines(t_box *map, char *av);
void    store_map(char **av, t_box *map);
void    chk_ber (int ac, char **av, t_box *map);
void    error_print (char *err_txt, t_box *map);
void	if_rectangular(t_box *map);
void	check_walls(t_box *map);
void	check_elements(t_box *map);
void    parcing(t_box *map, char **av);
void	flood_fill(t_box *map, int x, int y);
void    cleanup(t_box *map);

#endif