#include "so_long.h"

void	initialize(t_box *map)
{
	map->b_map = 0;
	map->l_map = 0;
	map->player = -1;
	map->collectables = -1;
	map->exit = -1;
	map->dup_collectables = 0;
	map->dup_exit = 0;
	map->player_x = -1;
	map->player_y = -1;
	map->map_store = NULL;
	map->map_dup = NULL;
}

/// @brief updates the height/length of the map (l_map) and checks empty lines from top and middle
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

/// @brief this is a function that stores the map in the struct (map_store and map_dup)
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
		if (ft_strlen(map->map_store[i++]) != map->b_map)
			error_print("map is not rectangular\n", map);
	if (map->b_map * map->l_map < 15)
		error_print("map is too small\n", map);
	if (map->l_map > 16 || map->b_map > 30)
		error_print("map is too big\n", map);
}

// RETURNS (-1) if top or bottom WALLS not closed. //
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

// RETURNS (-1) if side WALLS not closed. //
// void	check_side_walls(t_box *map)
// {
// 	int	i;

// 	i = 1;
// 	while (i < (map->l_map - 1))
// 	{
// 		if ((map->map_store[i][0] != '1') \
// 			|| (map->map_store[i][map->b_map - 1] != '1'))
// 			error_print("Left or Right wall is not closed\n", map);
// 		i++;
// 	}
// }

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
			{
				map->player++;
				map->player_x = j;
				map->player_y = i;
			}
			else if (map->map_store[i][j] == 'E')
				map->exit++;
			else if (map->map_store[i][j] == 'C')
				map->collectables++;
			else if (map->map_store[i][j] != '1' && map->map_store[i][j] != '0')
				error_print("Map contains other characters!!\n", map);
			j++;
		}
		i++;
	}
}

// int	elements_count(t_box *map)
// {
// 	if (map->player != 1)
// 	{
// 		error_print("Check the no. of Players!!");
// 		return (-1);
// 	}
// 	else if (map->exit != 1)
// 	{
// 		error_print("Check the no. of Exits!!");
// 		return (-1);
// 	}
// 	else if (map->collectables < 1)
// 	{
// 		error_print("Check the no. of Collectables!!");
// 		return (-1);
// 	}
// 	return (0);
// }

// char **map_dup(t_box *map)
// {
//     int i;

//     i = 0;
//     map->map_dup = malloc(sizeof(char *) * (map->l_map + 1));
//     if (!map->map_dup)
//         error_print("Failed to malloc for map->map_dup");
//     while (i < map->l_map)
// 	{
// 		map->map_dup[i] = ft_strdup(map->map_store[i]);
//         if (!map->map_dup[i])
//             error_print("Failed to duplicate map row");
//         i++;
//     }
//     map->map_dup[i] = NULL;
//     return (map->map_dup);
// }

// int	locate_player(t_box *map)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (map->map_store[i])
// 	{
// 		j = 0;
// 		while (map->map_store[i][j])
// 		{
// 			if (map->map_store[i][j] == 'P')
// 			{
// 				map->player_x = i;
// 				map->player_y = j;
// 				return (1);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	error_print("Player not found!");
// 	return (-1);
// }

void	flood_fill(t_box *map, int x, int y)
{
	if (x < 0 || y < 0 || x >= map->l_map || y >= map->b_map)
		return ;
	if (map->map_dup[x][y] == '1' || map->map_dup[x][y] == 'H')
		return ;
	if (map->map_dup[x][y] == 'C')
		map->dup_collectables--;
	if (map->map_dup[x][y] == 'E')
	{
		if (map->collectables == 0)
			map->dup_exit = 1;
		return ;
	}
	map->map_dup[x][y] = 'H';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

// int	success_fail(t_box *map)
// {
// 	if (map->collectables != 0)
// 	{
// 		error_print("Not all collectibles are reachable!");
// 		return (-1);
// 	}
// 	if (map->exit == 0)
// 	{
// 		error_print("The exit is not reachable!");
// 		return (-1);
// 	}
// 	return (0);
// }

// int	valid_map(t_box *map)
// {
// 	if (map->collectables == 0 && map->exit == 1)
// 		error_print("Map is filled & Valid");
// 	else
// 	{
// 		error_print("Map is NOT filled & Valid");
// 		return (-1);
// 	}
// 	return (0);
// }