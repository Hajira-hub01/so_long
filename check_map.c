#include "so_long.h"

void initialize(t_box *map, int ac, char **av)
{
	// t_box *map = NULL;

	map->player = 0;
	map->exit = 0;
	map->collectables = 0;
	map->b_map = 0;
	map->l_map = 0;
	map->ac = ac;
	map->av = av;
	map->map_store = NULL;
}

int	count_lines(char *map)
{
	int		i;
	char	*line;
	int		fd;

	i = 0;
	fd = open(map, O_RDONLY);
	if (fd == -1)
		error_print("unable to open the file in count_line");
	line = get_next_line(fd);
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (i);
}

// DONT FORGET TO free(map->map_store) EVERYWHERE U USE!!//
char	**store_map(char **av, t_box *map)
{
	int		fd;
	int		len;
	int		i;
	char	*line;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		error_print("unable to open the file (;w;)");
		close(fd);
	}
	len = 0;
	len = count_lines(av[1]);
	map->map_store = malloc(sizeof(char *) * (len + 1));
	if (!map->map_store)
		(error_print("Malloc Failed"), close(fd));
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		map->map_store[i] = ft_strdup_w_nl(line);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	map->map_store[i] = NULL;
	(free(line), close(fd));
	map->l_map = count_lines(av[1]);
	return (map->map_store);
}

// UPDATES the b_map //
int	if_rectangular(t_box *map)
{
	int	i;
	size_t	str1_len;

	i = 1;
	str1_len = ft_strlen(map->map_store[0]);
	while (map->map_store[i])
	{
		if (ft_strlen(map->map_store[i]) != str1_len)
		{
			error_print("map is not rectangular");
			return (-1);
		}
		i++;
	}
	map->b_map = str1_len;
	return (0);
}
// RETURNS (-1) if its NOT rectanngular. //

int	check_top_bottom_walls(t_box *map)
{
	int	last_l;
	int	i;

	i = -1;
	last_l = map->l_map;
	while (map->map_store[0][++i])
	{
		if (map->map_store[0][i] != '1' && map->map_store[0][i] != '\n')
		{
			error_print("Top wall not closed!");
			return (-1);
		}
	}
	i = -1;
	while (map->map_store[last_l - 1][++i])
	{
		if (map->map_store[last_l - 1][i] != '1' && map->map_store[0][i] != '\n')
		{
			error_print("Bottom wall not closed!");
			return (-1);
		}
	}
	return (0);
}
// RETURNS (-1) if top or bottom WALLS not closed. //

int	check_side_walls(t_box *map)
{
	int	i;

	i = 1;
	while (i < (map->l_map - 1))
	{
		if ((map->map_store[i][0] != '1') || (map->map_store[i][map->b_map - 1] != '1'))
		{
			error_print("Left or Right wall is not closed");
			return (-1);
		}
		i++;
	}
	return (0);
}
// RETURNS (-1) if side WALLS not closed. //

int	check_elements(t_box *map)
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
				map->collectables++;
			else if (map->map_store[i][j] != '1' && map->map_store[i][j] != '0')
			{
				error_print("Map contains other characters!!");
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	elements_count(t_box *map)
{
	if (map->player != 1)
	{
		error_print("Check the no. of Players!!");
		return (-1);
	}
	else if (map->exit != 1)
	{
		error_print("Check the no. of Exits!!");
		return (-1);
	}
	else if (map->collectables < 1)
	{
		error_print("Check the no. of Collectables!!");
		return (-1);
	}
	return (0);
}

char **map_dup(t_box *map) 
{
    int i;

    i = 0;
    map->map_dup = malloc(sizeof(char *) * (map->l_map + 1));
    if (!map->map_dup)
        error_print("Failed to malloc for map->map_dup");
    while (i < map->l_map) 
	{
		map->map_dup[i] = ft_strdup(map->map_store[i]);
        if (!map->map_dup[i])
            error_print("Failed to duplicate map row");
        i++;
    }
    map->map_dup[i] = NULL;
    return (map->map_dup);
}

int locate_player(t_box *map) 
{
    int i;
	int j;

	i = 0;

    while (map->map_store[i]) 
	{
        j = 0;
        while (map->map_store[i][j]) 
		{
            if (map->map_store[i][j] == 'P') 
			{
                map->player_x = i;
                map->player_y = j;
                return(1);
            }
            j++;
        }
        i++;
    }
    error_print("Player not found!");
	return(-1);
}

void	flood_fill(t_box *map, int x, int y)
{
	if (x < 0 || y < 0 || x >= map->l_map || y >= map->b_map)
		return ;
	if (map->map_dup[x][y] == '1' || map->map_dup [x][y] == 'H')
		return;
	if (map->map_dup[x][y] == 'C')
		map->collectables--;
	if (map->map_dup[x][y] == 'E')
	{
		if (map->collectables == 0)
			map->exit = 1;
		return;
	}
	map->map_dup[x][y] = 'H';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

int success_fail(t_box *map) 
{
    if (map->collectables != 0) 
	{
        error_print("Not all collectibles are reachable!");
        return (-1);
    }

    if (map->exit == 0) 
	{
        error_print("The exit is not reachable!");
        return (-1);
    }

    return (0);
}

int	valid_map(t_box *map)
{
	if (map->collectables == 0 && map->exit == 1)
		error_print("Map is filled & Valid");
	else
	{
		error_print("Map is NOT filled & Valid");
		return(-1);
	}
	return (0);
}