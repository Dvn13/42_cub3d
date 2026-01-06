/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_border_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:07:59 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/06 18:47:07 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static int	check_inner_spaces(char *row, int first, int last)
// {
// 	int	i;

// 	i = first;
// 	while (i <= last)
// 	{
// 		if (row[i] == ' ' && i > first && i < last)
// 		{
// 			if ((i > 0 && row[i - 1] != '1' && row[i - 1] != ' ')
// 				|| (row[i + 1] && row[i + 1] != '1' && row[i + 1] != ' '))
// 				return (0);
// 		}
// 		i++;
// 	}
// 	return (1);
// }

// static int	check_row_borders(char *row)
// {
// 	int	first;
// 	int	last;
// 	int	i;

// 	first = 0;
// 	while (row[first] && row[first] == ' ')
// 		first++;
// 	if (!row[first] || row[first] == '\n')
// 		return (1);
// 	if (row[first] != '1')
// 		return (0);
// 	last = 0;
// 	i = first;
// 	while (row[i] && row[i] != '\n')
// 	{
// 		if (row[i] != ' ')
// 			last = i;
// 		i++;
// 	}
// 	if (row[last] != '1')
// 		return (0);
// 	return (check_inner_spaces(row, first, last));
// }

// static int	find_last_row(t_world *world, int col)
// {
// 	int		last_row;
// 	char	cell;

// 	last_row = world->height - 1;
// 	while (last_row >= 0)
// 	{
// 		cell = world->grid[last_row][col];
// 		if (cell && cell != ' ' && cell != '\n')
// 			break ;
// 		last_row--;
// 	}
// 	return (last_row);
// }

// static int	check_column_borders(t_world *world, int col)
// {
// 	int		first_row;
// 	int		last_row;
// 	char	cell;

// 	first_row = 0;
// 	while (first_row < world->height)
// 	{
// 		cell = world->grid[first_row][col];
// 		if (cell && cell != ' ' && cell != '\n')
// 			break ;
// 		first_row++;
// 	}
// 	last_row = find_last_row(world, col);
// 	if (first_row >= world->height || last_row < 0)
// 		return (1);
// 	if (world->grid[first_row][col] != '1'
// 		|| world->grid[last_row][col] != '1')
// 		return (0);
// 	return (1);
// }

// int	check_map_borders(t_world *world)
// {
// 	int	i;

// 	// if (!world || !world->grid || world->height < 3 || world->width < 3)
// 	// 	return (0);
// 	i = 0;
// 	while (i < world->height)
// 	{
// 		if (!check_row_borders(world->grid[i]))
// 			return (0);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < world->width)
// 	{
// 		if (!check_column_borders(world, i))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

int	walk(char cell)
{
	if (!cell)
		return(0);
	if (cell == '0' || cell == 'N' || cell == 'S'
		|| cell == 'E' || cell == 'W' || cell == 'O' || cell == '1')
		return (1);
	return (0);
}

int check_map_borders(t_world *world)
{
	int i = 0;
	int j;
	while(world->grid[i])
	{
		j = -1;
		while (world->grid[i][++j])
		{
			if(world->grid[i][j] == '0')
			{
				if(i == 0 || world->grid[i + 1] == 0)
					return (0);
				if(!walk(world->grid[i][j + 1]) || !walk(world->grid[i][j - 1]) || !walk(world->grid[i + 1][j]) || !walk(world->grid[i - 1][j]))
					return (0);
			}	
		}
		i++;
	}
	return (1);
}
