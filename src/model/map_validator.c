#include "cub3d.h"

static int	validate_textures(t_map *map)
{
	if (!map->north_texture || !map->south_texture || 
		!map->east_texture || !map->west_texture)
		return (0);
	return (1);
}

static int	validate_colors(t_map *map)
{
	if (map->floor_color == -1 || map->ceiling_color == -1)
		return (0);
	return (1);
}

static int	count_players(t_map *map)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] == 'N' || map->grid[i][j] == 'S' || 
				map->grid[i][j] == 'E' || map->grid[i][j] == 'W')
				player_count++;
			j++;
		}
		i++;
	}
	return (player_count);
}

static int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || 
			c == 'E' || c == 'W' || c == ' ');
}

static int	validate_map_characters(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (!is_valid_map_char(map->grid[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	flood_fill_check(t_map *map, int x, int y, char **visited)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (0);
	if (visited[y][x] == '1')
		return (1);
	if (map->grid[y][x] == ' ')
		return (0);
	if (map->grid[y][x] == '1')
		return (1);
	visited[y][x] = '1';
	if (!flood_fill_check(map, x + 1, y, visited) ||
		!flood_fill_check(map, x - 1, y, visited) ||
		!flood_fill_check(map, x, y + 1, visited) ||
		!flood_fill_check(map, x, y - 1, visited))
		return (0);
	return (1);
}

static int	validate_map_closure(t_map *map)
{
	char	**visited;
	int		i;
	int		j;
	int		result;

	visited = ft_calloc(map->height, sizeof(char *));
	if (!visited)
		return (0);
	i = 0;
	while (i < map->height)
	{
		visited[i] = ft_calloc(map->width + 1, sizeof(char));
		if (!visited[i])
		{
			free_string_array(visited);
			return (0);
		}
		i++;
	}
	result = 1;
	i = 0;
	while (i < map->height && result)
	{
		j = 0;
		while (j < map->width && result)
		{
			if ((map->grid[i][j] == '0' || map->grid[i][j] == 'N' || 
				map->grid[i][j] == 'S' || map->grid[i][j] == 'E' || 
				map->grid[i][j] == 'W') && visited[i][j] != '1')
			{
				if (!flood_fill_check(map, j, i, visited))
					result = 0;
			}
			j++;
		}
		i++;
	}
	free_string_array(visited);
	return (result);
}

int	map_validate(t_map *map)
{
	if (!map || !map->grid)
		return (0);
	if (!validate_textures(map))
		return (0);
	if (!validate_colors(map))
		return (0);
	if (!validate_map_characters(map))
		return (0);
	map->player_count = count_players(map);
	if (map->player_count != 1)
		return (0);
	if (!validate_map_closure(map))
		return (0);
	return (1);
}

int	map_is_wall(t_map *map, int x, int y)
{
	if (!map || !map->grid)
		return (1);
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (1);
	return (map->grid[y][x] == '1');
}

char	map_get_cell(t_map *map, int x, int y)
{
	if (!map || !map->grid)
		return ('1');
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return ('1');
	return (map->grid[y][x]);
}