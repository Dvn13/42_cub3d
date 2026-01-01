/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:52:32 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/01 15:16:37 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_world	*world_create(void)
{
	t_world	*world;

	world = safe_calloc(1, sizeof(t_world));
	if (!world)
		return (NULL);
	world->grid = NULL;
	world->width = 0;
	world->height = 0;
	world->north_texture_path = NULL;
	world->south_texture_path = NULL;
	world->east_texture_path = NULL;
	world->west_texture_path = NULL;
	world->floor_color = 0x473E37;
	world->ceiling_color = 0xD8E3E7;
	world->character_count = 0;
	world->floor_texture_path = NULL;
    world->ceiling_texture_path = NULL;
	world->door_texture_path = NULL;
	return (world);
}

int	world_is_wall(t_world *world, int x, int y)
{
	char cell;

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

void	world_destroy(t_world *world)
{
	int	i;

	if (!world)
		return ;
	if (world->grid)
	{
		i = 0;
		while (i < world->height)
		{
			if (world->grid[i])
				safe_free(world->grid[i]);
			i++;
		}
		safe_free(world->grid);
	}
	if (world->north_texture_path)
		safe_free(world->north_texture_path);
	if (world->south_texture_path)
		safe_free(world->south_texture_path);
	if (world->east_texture_path)
		safe_free(world->east_texture_path);
	if (world->west_texture_path)
		safe_free(world->west_texture_path);
	if (world->door_texture_path)
		safe_free(world->door_texture_path);
	safe_free(world);
}
