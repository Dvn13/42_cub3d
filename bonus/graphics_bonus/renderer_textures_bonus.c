/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_textures_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdivan <mdivan@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 04:03:16 by mdivan            #+#    #+#             */
/*   Updated: 2026/01/03 04:03:19 by mdivan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	load_floor_ceiling_textures(t_engine *engine)
{
	if (engine->world->floor_texture_path)
	{
		engine->renderer->floor_texture = texture_allocate();
		if (!texture_load_from_file(engine->renderer->floor_texture,
				engine->mlx_ptr, engine->world->floor_texture_path))
			return (0);
	}
	else
		engine->renderer->floor_texture = NULL;
	if (engine->world->ceiling_texture_path)
	{
		engine->renderer->ceiling_texture = texture_allocate();
		if (!texture_load_from_file(engine->renderer->ceiling_texture,
				engine->mlx_ptr, engine->world->ceiling_texture_path))
			return (0);
	}
	else
		engine->renderer->ceiling_texture = NULL;
	return (1);
}

static int	load_door_texture(t_engine *engine)
{
	if (!engine->world->door_texture_path)
	{
		engine->world->door_texture_path
			= duplicate_string("./assets/textures/door.xpm");
		if (!engine->world->door_texture_path)
			return (0);
	}
	engine->renderer->door_texture = texture_allocate();
	if (!engine->renderer->door_texture)
		return (0);
	if (!texture_load_from_file(engine->renderer->door_texture, engine->mlx_ptr,
			engine->world->door_texture_path))
		return (0);
	return (1);
}

static int	load_sprite_textures(t_engine *engine)
{
	int		i;
	char	*base_path;
	char	path[100];

	i = 0;
	base_path = "assets/sprites/Gold_";
	while (i < 10)
	{
		engine->renderer->sprite_textures[i] = texture_allocate();
		sprintf(path, "%s%d.xpm", base_path, 21 + i);
		if (!texture_load_from_file(engine->renderer->sprite_textures[i],
				engine->mlx_ptr, path))
			return (0);
		i++;
	}
	return (1);
}

int	load_bonus_textures(t_engine *engine)
{
	if (!load_floor_ceiling_textures(engine))
		return (0);
	if (!load_door_texture(engine))
		return (0);
	if (!load_sprite_textures(engine))
		return (0);
	return (1);
}

void	destroy_bonus_textures(t_renderer *renderer, void *mlx_ptr)
{
	if (renderer->floor_texture)
	{
		if (renderer->floor_texture->image_ptr)
			mlx_destroy_image(mlx_ptr, renderer->floor_texture->image_ptr);
		safe_free(renderer->floor_texture);
	}
	if (renderer->ceiling_texture)
	{
		if (renderer->ceiling_texture->image_ptr)
			mlx_destroy_image(mlx_ptr, renderer->ceiling_texture->image_ptr);
		safe_free(renderer->ceiling_texture);
	}
	if (renderer->door_texture)
	{
		if (renderer->door_texture->image_ptr)
			mlx_destroy_image(mlx_ptr, renderer->door_texture->image_ptr);
		safe_free(renderer->door_texture);
	}
}
