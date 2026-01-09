/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdivan <mdivan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:52:32 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/09 10:16:04 by mdivan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	world_validate(t_world *world)
{
	if (!world || !world->grid)
		return (report_error("Map data is missing or empty"));
	if (!count_map_players(world))
		return (0);
	if (!init_sprite_positions(world))
		return (0);
	if (!check_textures_loaded(world))
		return (0);
	if (!check_floor_ceiling_set(world))
		return (0);
	if (!check_map_closed(world))
		return (0);
	return (1);
}

int	world_is_wall(t_world *world, int x, int y)
{
	char	cell;

	if (!world || !world->grid || x < 0 || y < 0 || x >= world->width
		|| y >= world->height)
		return (1);
	cell = world->grid[y][x];
	if (cell == '1' || cell == 'D')
		return (1);
	return (0);
}

char	world_get_cell(t_world *world, int x, int y)
{
	if (!world || !world->grid || x < 0 || y < 0 || x >= world->width
		|| y >= world->height)
		return (' ');
	return (world->grid[y][x]);
}
