/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:43:32 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/02 17:44:07 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	world->floor_color = -1;
	world->ceiling_color = -1;
	world->character_count = 0;
	return (world);
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
	safe_free(world);
}
