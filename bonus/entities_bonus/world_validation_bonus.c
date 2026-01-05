/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_validation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:43:50 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/05 17:12:39 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	check_row_borders(char *row)
{
	int	first;
	int	last;
	int	i;

	first = 0;
	while (row[first] && row[first] == ' ')
		first++;
	if (!row[first] || row[first] == '\n')
		return (1);
	if (row[first] != '1')
		return (0);
	last = 0;
	i = first;
	while (row[i] && row[i] != '\n')
	{
		if (row[i] != ' ')
			last = i;
		i++;
	}
	if (row[last] != '1')
		return (0);
	i = first;
	while (i <= last)
	{
		if (row[i] == ' ' && i > first && i < last)
		{
			if ((i > 0 && row[i - 1] != '1' && row[i - 1] != ' ')
				|| (row[i + 1] && row[i + 1] != '1' && row[i + 1] != ' '))
				return (0);
		}
		i++;
	}
	return (1);
}

static int	check_map_borders(t_world *world)
{
	int	i;

	if (!world || !world->grid || world->height < 3 || world->width < 3)
		return (0);
	i = 0;
	while (i < world->height)
	{
		if (!check_row_borders(world->grid[i]))
			return (0);
		i++;
	}
	return (1);
}

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

static int	is_valid_walkable_cell(char cell)
{
	if (cell == '0' || cell == 'N' || cell == 'S'
		|| cell == 'E' || cell == 'W' || cell == 'O' || cell == SPRITE_CHAR)
		return (1);
	return (0);
}

int	flood_fill(t_world *world, char **map, int x, int y)
{
	char	cell;

	if (y < 0 || y >= world->height || x < 0 || x >= world->width)
		return (0);
	if (!map[y])
		return (0);
	cell = map[y][x];
	if (cell == '\0' || cell == '\n' || cell == '\r')
		return (0);
	if (cell == '1' || cell == 'V' || cell == 'D')
		return (1);
	if (cell == ' ' || cell == '\t')
	{
		if (x == world->width - 1 || y == 0 || y == world->height - 1 || x == 0)
			return (1);
		return (0);
	}
	if (!is_valid_walkable_cell(cell))
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

	if (!check_map_borders(world))
		return (0);
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
