/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:43:50 by gbodur            #+#    #+#             */
/*   Updated: 2025/12/22 19:24:58 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char **duplicate_map(t_world *world)
{
	char **map_copy;
	int		i;
	
	map_copy = malloc(sizeof(char *) * (world->height + 1));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < world->height)
	{
		map_copy[i] = duplicate_string(world->grid[i]);
		if (!map_copy[i])
		{
			free_string_array(map_copy);
			return (NULL);
		}
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

static int flood_fill(t_world *world, char  **map, int x, int y)
{
	int	rows;
	int	cols;

	rows = world->height;
	if (y < 0 || y >= rows || !map[y])
		return (0);
	
	cols = string_length(map[y]);
	if (x < 0 || x >= cols)
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (1);
	if (map[y][x] == ' ' || map[y][x] == '\t')
		return (0);
	map[y][x] = 'V';
	if (!flood_fill(world, map, x + 1, y))
		return (0);
	if (!flood_fill(world, map, x - 1, y))
		return (0);
	if (!flood_fill(world, map, x, y + 1))
		return (0);
	if (!flood_fill(world, map, x, y - 1))
		return (0);

	return (1);
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
	
	free_string_array(map_copy);
	return (1);
}
