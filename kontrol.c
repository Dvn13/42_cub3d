int	full_map_check(t_world	*world, char **map_copy)
{
	int		x;
	int		y;
	int		player_found;
	
	player_found = 0;
	y = 0;
	while (y < world->height && !player_found)
	{
		x = 0;
		while (map_copy[y][x])
		{
			if (map_copy[y][x] == 'N' || map_copy[y][x] == 'S' ||
				map_copy[y][x] == 'E' || map_copy[y][x] == 'W')
			{
				player_found = 1;
				break ;
			}
			x++;
		}
		if (!player_found)
			y++;
	}
	if (!player_found || !flood_fill(world, map_copy, x, y))
	{
		free_string_array(map_copy);
		return (0);
	}
	return (0);
}

int	check_map_closed(t_world *world)
{
	char	**map_copy;
	int		x;
	int		y;
	int		player_found;

	map_copy = duplicate_map(world);
	if (!map_copy)
		return (0);
	player_found = 0;
	y = 0;
	full_map_check(world, &map_copy);
	free_string_array(map_copy);
	return (1);
}