/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_setup_validation_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdivan <mdivan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 19:50:15 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/08 20:25:51 by mdivan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	check_floor_ceiling_set(t_world *world)
{
	if (world->floor_color == -1 && world->floor_texture_path == NULL)
	{
		report_error("Missing Floor specification (F: Color or Texture)");
		return (0);
	}
	if (world->ceiling_color == -1 && world->ceiling_texture_path == NULL)
	{
		report_error("Missing Ceiling specification(C: Color or Texture)");
		return (0);
	}
	return (1);
}

int	check_textures_loaded(t_world *world)
{
	if (!world->north_texture_path)
		return (report_error("Missing North texture (NO)"));
	if (!world->south_texture_path)
		return (report_error("Missing South texture (SO)"));
	if (!world->west_texture_path)
		return (report_error("Missing West texture (WE)"));
	if (!world->east_texture_path)
		return (report_error("Missing East texture (EA)"));
	return (1);
}

static void	fill_sprite_array(t_world *world)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (i < world->height)
	{
		j = 0;
		while (world->grid[i][j])
		{
			if (world->grid[i][j] == SPRITE_CHAR)
			{
				world->sprites[k].x = j + 0.5;
				world->sprites[k].y = i + 0.5;
				world->sprites[k].texture_id = 0;
				world->sprites[k].dist = 0;
				world->sprites[k].is_collected = 0;
				world->grid[i][j] = '0';
				k++;
			}
			j++;
		}
		i++;
	}
}

int	init_sprite_positions(t_world *world)
{
	if (world->sprite_count == 0)
		return (1);
	world->sprites = malloc(sizeof(t_sprite) * world->sprite_count);
	if (!world->sprites)
		return (report_error("Memory allocation for sprites failed"));
	fill_sprite_array(world);
	return (1);
}

int	count_map_players(t_world *world)
{
	int	i;
	int	j;

	i = -1;
	while (++i < world->height)
	{
		j = -1;
		while (world->grid[i][++j])
		{
			if (world->grid[i][j] == 'N' || world->grid[i][j] == 'S' ||
				world->grid[i][j] == 'E' || world->grid[i][j] == 'W')
			{
				world->character_count++;
				world->py = i;
				world->px = j;
			}
			else if (world->grid[i][j] == SPRITE_CHAR)
			{
				world->sprite_count++;
			}
		}
	}
	if (world->character_count != 1)
		return (report_error("Map should contain just one player(N, S, E, W)"));
	return (1);
}
