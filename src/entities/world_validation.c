/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:43:50 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/02 17:46:39 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static int	flood_fill(t_world *world, char **map, int x, int y)
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

static int	find_and_check_player(t_world	*world, char **map_copy, int *x,
	int *y)
{
	int	player_found;
	int	row;
	int	col;

	player_found = 0;
	row = 0;
	while (row < world->height && !player_found)
	{
		col = 0;
		while (map_copy[row][col])
		{
			if (map_copy[row][col] == 'N' || map_copy[row][col] == 'S' ||
				map_copy[row][col] == 'E' || map_copy[row][col] == 'W')
			{
				*x = col;
				*y = row;
				player_found = 1;
				break ;
			}
			col++;
		}
		if (!player_found)
			row++;
	}
	return (player_found);
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
	if (find_and_check_player(world, map_copy, &x, &y))
	{
		if (flood_fill(world, map_copy, x, y))
			is_valid = 1;
	}
	free_string_array(map_copy);
	return (is_valid);
}
