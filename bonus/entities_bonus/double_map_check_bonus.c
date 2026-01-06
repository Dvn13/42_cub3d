/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_map_check_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 11:09:07 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/06 11:13:25 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_valid_walkable_cell(char cell)
{
	if (cell == '0' || cell == 'N' || cell == 'S'
		|| cell == 'E' || cell == 'W' || cell == 'O' || cell == SPRITE_CHAR)
		return (1);
	return (0);
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

int	check_double_map_in_row(t_world *world, int row_idx)
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
