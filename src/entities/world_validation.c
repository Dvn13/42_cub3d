/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:43:50 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/08 18:58:28 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	walk(char cell)
{
	if (!cell)
		return (0);
	if (cell == '0' || cell == 'N' || cell == 'S'
		|| cell == 'E' || cell == 'W' || cell == '1')
		return (1);
	return (0);
}

static int	check_map_borders(t_world *world)
{
	int	i;
	int	j;

	i = 0;
	while (world->grid[i])
	{
		j = -1;
		while (world->grid[i][++j])
		{
			if (world->grid[i][j] == '0' || world->grid[i][j] == 'N'
				|| world->grid[i][j] == 'S' || world->grid[i][j] == 'E'
				|| world->grid[i][j] == 'W')
			{
				if (i == 0 || world->grid[i + 1] == 0)
					return (0);
				if (!walk(world->grid[i][j + 1]) || !walk(world->grid[i][j - 1])
					|| !walk(world->grid[i + 1][j])
					|| !walk(world->grid[i - 1][j]))
					return (0);
			}	
		}
		i++;
	}
	return (1);
}

int	check_map_closed(t_world *world)
{
	if (!check_map_borders(world))
		return (report_error("Map is not closed or surrounded by walls"));
	if (!check_space_map(world))
		return (report_error("Map contains unreachable areas or double map"));
	return (1);
}
