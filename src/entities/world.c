/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdivan <mdivan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:52:32 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/08 19:58:43 by mdivan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	world_check_textures_and_colors(t_world *world)
{
	if (!world || !world->grid)
		return (0);
	if (!world->north_texture_path || !world->south_texture_path
		|| !world->east_texture_path || !world->west_texture_path)
		return (report_error("Missing texture (NO, SO, EA, WE)"));
	if (world->floor_color == -1 || world->ceiling_color == -1)
		return (report_error("Missing color codes (F, C)"));
	return (1);
}

int	find_player(t_world *world)
{
	int	i;
	int	j;

	i = 0;
	while (i < world->height)
	{
		j = 0;
		while (j < world->width)
		{
			if (world->grid[i][j] == 'N' || world->grid[i][j] == 'S'
				|| world->grid[i][j] == 'E' || world->grid[i][j] == 'W')
			{
				world->character_count++;
				world->px = j;
				world->py = i;
			}
			j++;
		}
		i++;
	}
	if (world->character_count != 1)
		return (report_error("Map should contain just one player(N, S, E, W)"));
	return (1);
}

int	world_validate(t_world *world)
{
	if (!world_check_textures_and_colors(world))
		return (0);
	if (!find_player(world))
		return (0);
	return (1);
}

int	world_is_wall(t_world *world, int x, int y)
{
	if (!world || !world->grid || x < 0 || y < 0 || x >= world->width
		|| y >= world->height)
		return (1);
	return (world->grid[y][x] == WALL_SYMBOL);
}
