/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:43:50 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/05 20:21:11 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_vertical_neighbors(t_world *world, int row, int col)
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
	return (1);
}

static int	check_space_neighbors(t_world *world, int row, int col)
{
	char	cell;

	if (!check_vertical_neighbors(world, row, col))
		return (0);
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
