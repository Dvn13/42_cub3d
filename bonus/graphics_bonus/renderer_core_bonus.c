/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_core_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:18:21 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/02 13:29:19 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_renderer	*renderer_create(void *mlx_ptr)
{
	t_renderer	*renderer;

	renderer = safe_calloc(1, sizeof(t_renderer));
	if (!renderer)
		return (NULL);
	renderer->image_ptr = mlx_new_image(mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!renderer->image_ptr)
	{
		safe_free(renderer);
		return (NULL);
	}
	renderer->image_data = mlx_get_data_addr(renderer->image_ptr,
			&renderer->bits_per_pixel, &renderer->size_line, &renderer->endian);
	renderer->image_width = SCREEN_WIDTH;
	renderer->image_height = SCREEN_HEIGHT;
	renderer->z_buffer = safe_calloc(SCREEN_WIDTH, sizeof(double));
	if (!renderer->z_buffer)
	{
		renderer_destroy(renderer, mlx_ptr);
		return (NULL);
	}
	renderer->sprite_textures = safe_calloc(10, sizeof(t_texture *));
	if (!renderer->sprite_textures)
	{
		renderer_destroy(renderer, mlx_ptr);
		return (NULL);
	}
	renderer->sprite_text_count = 10;
	return (renderer);
}

int load_bonus_textures(t_engine *engine)
{
	int i;
    char *base_path;
    char path[100];
	
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
	if (!engine->world->door_texture_path )
	{
		engine->world->door_texture_path
			= duplicate_string("./assets/textures/door.xpm");
		if (!engine->world->door_texture_path)
            return (0);
	}
	engine->renderer->door_texture = texture_allocate();
	if (!engine->renderer->door_texture)
        return (0);
	if (!texture_load_from_file(engine->renderer->door_texture,
		engine->mlx_ptr, engine->world->door_texture_path))
		return (0);
	i = 0;
    base_path = "assets/sprites/Gold_";
	while (i < 10)
    {
        engine->renderer->sprite_textures[i] = texture_allocate();
        sprintf(path, "%s%d.xpm", base_path, 21 + i);
        if (!texture_load_from_file(engine->renderer->sprite_textures[i], engine->mlx_ptr, path))
            return (0);
        i++;
    }
    return (1);
}

void	renderer_destroy(t_renderer *renderer, void *mlx_ptr)
{
	if (!renderer)
		return ;
	if (renderer->image_ptr)
		mlx_destroy_image(mlx_ptr, renderer->image_ptr);
	if (renderer->z_buffer)
		safe_free(renderer->z_buffer);
	if (renderer->sprite_textures)
	{
		int i = 0;
		while (i < renderer->sprite_text_count)
		{
			if (renderer->sprite_textures[i])
				texture_destroy(renderer->sprite_textures[i], mlx_ptr);
			i++;
		}
		safe_free(renderer->sprite_textures);
	}
	safe_free(renderer);
}

void	renderer_clear_screen(t_renderer *renderer, int color)
{
	int	x;
	int	y;

	if (!renderer || !renderer->image_data)
		return ;
	y = 0;
	while (y < renderer->image_height)
	{
		x = 0;
		while (x < renderer->image_width)
		{
			renderer_put_pixel(renderer, x, y, color);
			x++;
		}
		y++;
	}
}

void	renderer_draw_to_window(t_renderer *renderer, void *mlx_ptr,
		void *win_ptr)
{
	if (!renderer || !renderer->image_ptr)
		return ;
	mlx_put_image_to_window(mlx_ptr, win_ptr, renderer->image_ptr, 0, 0);
}
