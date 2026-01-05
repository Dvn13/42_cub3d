/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_validation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:43:50 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/05 19:43:17 by gbodur           ###   ########.fr       */
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

static int	check_column_borders(t_world *world, int col)
{
	int		first_row;
	int		last_row;
	char	cell;

	first_row = 0;
	while (first_row < world->height)
	{
		cell = world->grid[first_row][col];
		if (cell && cell != ' ' && cell != '\n')
			break ;
		first_row++;
	}
	last_row = world->height - 1;
	while (last_row >= 0)
	{
		cell = world->grid[last_row][col];
		if (cell && cell != ' ' && cell != '\n')
			break ;
		last_row--;
	}
	if (first_row >= world->height || last_row < 0)
		return (1);
	if (world->grid[first_row][col] != '1'
		|| world->grid[last_row][col] != '1')
		return (0);
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
	i = 0;
	while (i < world->width)
	{
		if (!check_column_borders(world, i))
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

static int	is_valid_walkable_cell(char cell)
{
	if (cell == '0' || cell == 'N' || cell == 'S'
		|| cell == 'E' || cell == 'W' || cell == 'O' || cell == SPRITE_CHAR)
		return (1);
	return (0);
}

static int	check_space_neighbors(t_world *world, int row, int col)
{
	char	cell;

	if (row > 0)
	{
		cell = world->grid[row - 1][col];
		if (cell && is_valid_walkable_cell(cell))
			return (0);
	}
	if (row < world->height - 1)
	{
		cell = world->grid[row + 1][col];
		if (cell && is_valid_walkable_cell(cell))
			return (0);
	}
	if (col > 0)
	{
		cell = world->grid[row][col - 1];
		if (cell && is_valid_walkable_cell(cell))
			return (0);
	}
	if (world->grid[row][col + 1])
	{
		cell = world->grid[row][col + 1];
		if (is_valid_walkable_cell(cell))
			return (0);
	}
	return (1);
}

static int	check_all_spaces(t_world *world)
{
	int	row;
	int	col;

	row = 0;
	while (row < world->height)
	{
		col = 0;
		while (world->grid[row][col])
		{
			if (world->grid[row][col] == ' ')
			{
				if (!check_space_neighbors(world, row, col))
					return (0);
			}
			col++;
		}
		row++;
	}
	return (1);
}

static int	has_wall_after_space(char *row, int start)
{
	int	i;

	i = start;
	while (row[i] && row[i] != '\n')
	{
		if (row[i] == '1')
			return (1);
		if (row[i] != ' ')
			return (0);
		i++;
	}
	return (0);
}

static int	count_vertical_spaces(t_world *world, int col)
{
	int	count;
	int	row;

	count = 0;
	row = 0;
	while (row < world->height)
	{
		if (world->grid[row][col] && world->grid[row][col] == ' ')
			count++;
		row++;
	}
	return (count);
}

static int	check_vertical_space_separation(t_world *world, int col)
{
	return (count_vertical_spaces(world, col) >= world->height / 2);
}

static int	check_double_map_in_row(t_world *world, int row_idx)
{
	char	*row;
	int		i;
	int		found_content;

	row = world->grid[row_idx];
	i = 0;
	found_content = 0;
	while (row[i] && row[i] != '\n')
	{
		if (row[i] == '1' || is_valid_walkable_cell(row[i]))
			found_content = 1;
		if (row[i] == ' ' && found_content && has_wall_after_space(row, i + 1))
		{
			if (check_vertical_space_separation(world, i))
				return (0);
		}
		i++;
	}
	return (1);
}

static int	check_double_map(t_world *world)
{
	int	row;

	row = 0;
	while (row < world->height)
	{
		if (!check_double_map_in_row(world, row))
			return (0);
		row++;
	}
	return (1);
}

int	check_map_closed(t_world *world)
{
	if (!check_map_borders(world))
		return (0);
	if (!check_all_spaces(world))
		return (0);
	if (!check_double_map(world))
		return (0);
	return (1);
}
