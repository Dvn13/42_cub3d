/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:52:32 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/02 18:16:11 by gbodur           ###   ########.fr       */
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

int	world_validate(t_world *world)
{
	int	i;
	int	j;
	int	character_count;

	if (!world_check_textures_and_colors(world))
		return (0);
	character_count = 0;
	i = 0;
	while (i < world->height)
	{
		j = 0;
		while (j < world->width)
		{
			if (world->grid[i][j] == 'N' || world->grid[i][j] == 'S'
				|| world->grid[i][j] == 'E' || world->grid[i][j] == 'W')
				character_count++;
			j++;
		}
		i++;
	}
	world->character_count = character_count;
	if (character_count != 1)
		return (report_error("Map should contain just one player(N, S, E, W)"));
	return (1);
}

int	world_is_wall(t_world *world, int x, int y)
{
	if (!world || !world->grid || x < 0 || y < 0 || x >= world->width
		|| y >= world->height)
		return (1);
	return (world->grid[y][x] == WALL_SYMBOL);
}

char	world_get_cell(t_world *world, int x, int y)
{
	if (!world || !world->grid || x < 0 || y < 0 || x >= world->width
		|| y >= world->height)
		return (' ');
	return (world->grid[y][x]);
}
