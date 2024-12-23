void free_map_store(t_box *map) 
{
    int i = 0;

    while (map->map_store[i]) 
    {
        free(map->map_store[i]); // Free each row
        i++;
    }
    free(map->map_store); // Free the array itself
    map->map_store = NULL;
}

void free_map_dup(t_box *map) 
{
    int i = 0;

    while (map->map_dup[i]) 
    {
        free(map->map_dup[i]); // Free each row
        i++;
    }
    free(map->map_dup); // Free the array itself
    map->map_dup = NULL;
}

