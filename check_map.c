#include "so_long.h"

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
		map->map_store[i] = ft_strdup(line);
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
	int	str1_len;

	i = 1;
	str1_len = ft_strlen(map->map_store[0]);
	while (map->map_store[i])
	{	printf(" 1 %zu \n", ft_strlen(map->map_store[i]));
			printf("1 strlen  %d \n", str1_len);
		if (ft_strlen(map->map_store[i]) != str1_len)
		{
		printf("2 %zu\n",ft_strlen(map->map_store[i]));
			printf("2 strlen  %d \n", str1_len);
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

	i = 0;
	last_l = map->l_map;
	while (map->map_store[0][i])
	{
		// printf("map = %c\n", map->map_store[0][i]);
		if (map->map_store[0][i] != '1' && map->map_store[0][i] != '\n')
		{
			error_print("Top wall not closed!");
			return (-1);
		}
		i++;
	}
	i = 0;
	while (map->map_store[last_l - 1][i])
	{
		if (map->map_store[last_l - 1][i] != '1' && map->map_store[0][i] != '\n')
		{
			error_print("Bottom wall not closed!");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	check_side_walls(t_box *map)
{
	int i = 1;

    while (i < (map->l_map - 1)) 
	{
        if ((map->map_store[i][0] != '1') || (map->map_store[i][map->b_map - 2] != '1'))
        {
			error_print("Left or Right wall is not closed");
			return (-1);
		}
        i++;
    }
    return (0);
}

int main(int ac, char **av)
{
    if (ac != 2)
        error_print("Error: Expected one map file as an argument");

    t_box *map = malloc(sizeof(t_box));
    if (!map)
        error_print("Error: Memory allocation failed for map");

    // Store map and check if successfully loaded
    char **arr = store_map(av, map);
    if (!arr)
    {
        free(map);
        error_print("Error: Failed to load map");
    }

    // Perform rectangular check and free on failure
    if (if_rectangular(map) == -1)
    {
        free(map);
        for (int i = 0; arr[i]; i++)
            free(arr[i]);
        free(arr);
        exit(EXIT_FAILURE);
    }

    // Check top/bottom and side walls
    if (check_top_bottom_walls(map) == -1 || check_side_walls(map) == -1)
    {
        free(map);
        for (int i = 0; arr[i]; i++)
            free(arr[i]);
        free(arr);
        exit(EXIT_FAILURE);
    }

    // Print the map if all checks pass (for debugging)
    for (int i = 0; arr[i]; i++)
        printf("%s", arr[i]);

    // Clean up memory
    for (int i = 0; arr[i]; i++)
        free(arr[i]);
    free(arr);
    free(map);

    return (0);
}