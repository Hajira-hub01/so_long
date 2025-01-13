/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 12:28:54 by hajmoham          #+#    #+#             */
/*   Updated: 2025/01/13 19:25:36 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/// @brief updates the height/length of the map (l_map) and checks empty
// lines from top and middle
void	count_lines(t_box *map, char *av)
{
	char	*line;
	int		fd;
	int		empty;

	empty = 0;
	fd = open(av, O_RDONLY);
	if (fd == -1)
		error_print("unable to open the file in count_line\n", map);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '\n')
			empty = 1;
		if (line[0] != '\n' && line[0] != '\0' && empty)
			(free(line), error_print("Empty line found\n", map));
		if (line[0] != '\n' && line[0] != '\0')
			map->l_map++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	if (!map->l_map)
		error_print("Empty map file\n", map);
}

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

/// @brief  updates the breadth of the map (b_map) & if its a rectangle
void	if_rectangular(t_box *map)
{
	int	i;

	i = 1;
	map->b_map = ft_strlen(map->map_store[0]);
	while (map->map_store[i])
		if ((int)ft_strlen(map->map_store[i++]) != map->b_map)
			error_print("map is not rectangular\n", map);
	if (map->b_map * map->l_map < 15)
		error_print("map is too small\n", map);
	if (map->l_map > 16 || map->b_map > 30)
		error_print("map is too big\n", map);
}

/// @brief  checks the if the map top & bottom and sides are 1's
void	check_walls(t_box *map)
{
	int	i;

	i = -1;
	while (map->map_store[0][++i])
	{
		if (map->map_store[0][i] != '1' || map->map_store[map->l_map
			- 1][i] != '1')
			error_print("Top or Bottom wall not closed!\n", map);
	}
	i = 1;
	while (i < (map->l_map - 1))
	{
		if ((map->map_store[i][0] != '1') \
			|| (map->map_store[i][map->b_map - 1] != '1'))
			error_print("Left or Right wall is not closed\n", map);
		i++;
	}
}

/// @brief  checks the presnce of elements and counts them
void	check_elements(t_box *map)
{
	int	i;
	int	j;

	i = 1;
	while (map->map_store[i])
	{
		j = 0;
		while (map->map_store[i][j])
		{
			if (map->map_store[i][j] == 'P')
				map->player++;
			else if (map->map_store[i][j] == 'E')
				map->exit++;
			else if (map->map_store[i][j] == 'C')
				map->collectibles++;
			else if (map->map_store[i][j] != '1' && map->map_store[i][j] != '0')
				error_print("Map contains other characters!!\n", map);
			j++;
		}
		i++;
	}
}

/// @brief  checks if the pathway of map is valid
void	flood_fill(t_box *map, int x, int y)
{
	if (x == map->exit_x && y == map->exit_y)
	{
		map->dup_exit = 0;
		return ;
	}
	if (x < 0 || y < 0 || y >= map->l_map || x >= map->b_map)
		return ;
	if (map->map_dup[y][x] == '1' || map->map_dup[y][x] == 'H')
		return ;
	if (map->map_dup[y][x] == 'C')
		map->dup_collectibles--;
	if (map->map_dup[y][x] == 'E')
		map->dup_exit--;
	map->map_dup[y][x] = 'H';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}
	
// void	flood_fill(t_box *map, int x, int y)
// {
// 	if (x < 0 || y < 0 || x >= map->l_map || y >= map->b_map)
// 		return ;
// 	if (map->map_dup[x][y] == '1' || map->map_dup[x][y] == 'H')
// 		return ;
// 	if (map->map_dup[x][y] == 'C')
// 		map->dup_collectibles--;
// 	if (map->map_dup[x][y] == 'E')
// 		map->dup_exit--;
// 	map->map_dup[x][y] = 'H';
// 	flood_fill(map, x + 1, y);
// 	flood_fill(map, x - 1, y);
// 	flood_fill(map, x, y + 1);
// 	flood_fill(map, x, y - 1);
// }