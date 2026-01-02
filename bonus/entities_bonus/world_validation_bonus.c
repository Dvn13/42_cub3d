/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_validation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:43:50 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/02 20:01:38 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	check_player_exists(t_world *world)
{
	if (world->character_count == 0)
		return (report_error("Map missing player start position (N,S,E,W)"));
	if (world->character_count > 1)
		return (report_error("Map has multiple player start positions"));
	return (1);
}

static char	**duplicate_map(t_world *world)
{
	char	**map_copy;
	int		i;

	i = 0;
	map_copy = malloc(sizeof(char *) * (world->height + 1));
	if (!map_copy)
		return (NULL);
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

int	flood_fill(t_world *world, char **map, int x, int y)
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

static int	find_start_pos(char **map, int *x, int *y)
{
	int	row;
	int	col;

	row = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if (map[row][col] == 'N' || map[row][col] == 'S' ||
				map[row][col] == 'E' || map[row][col] == 'W')
			{
				*x = col;
				*y = row;
				return (1);
			}
			col++;
		}
		row++;
	}
	return (0);
}

int	check_map_closed(t_world *world)
{
	char	**map_copy;
	int		x;
	int		y;
	int		is_valid;

	map_copy = duplicate_map(world);
	if (!map_copy)
		return (0);
	is_valid = 0;
	if (find_start_pos(map_copy, &x, &y))
	{
		if (flood_fill(world, map_copy, x, y))
			is_valid = 1;
	}
	free_string_array(map_copy);
	return (is_valid);
}
