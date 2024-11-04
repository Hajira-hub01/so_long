#include "so_long.h"

int count_lines(char *map)
{
    int i;
    char *line;
    int fd = open(map, O_RDONLY);
    line = get_next_line(fd);
    while (line)
    {
        i++;
        line = get_next_line(fd);
    } 
    return(i);
}

char **store_map(char **av, t_box *map) 
{
    int fd = open(av[1], O_RDONLY);
    if (fd == -1) 
        error_print("unable to open the file (;w;)");

    char **map_store = malloc(sizeof(char *) * count_lines(av[1]));
    if (!map_store) 
    {
        error_print("Malloc Failed");
        close(fd);
    }
    int i = 0;
    char *line;
    line = get_next_line(fd);
    while (line) 
    {
        map_store[i] = ft_strdup(line);
        i++;
        free(line);
        line = get_next_line(fd);
    }
    free(line);
    map_store[i] = NULL;
    close(fd);
    map->l_map = count_lines(av[1]);
    return map_store;
}

int main(int ac, char **av)
{
    char **arr = store_map(av);

    int i = 0;

    while(arr[i])
    {
        printf("%s", arr[i]);
        i++;
    }
}