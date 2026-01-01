/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_init_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:31:30 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/01 13:27:47 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	initialize_mlx(t_engine *engine)
{
	engine->mlx_ptr = mlx_init();
	if (!engine->mlx_ptr)
	{
		report_error("MLX initialization failed");
		return (0);
	}
	engine->win_ptr = mlx_new_window(engine->mlx_ptr, SCREEN_WIDTH,
			SCREEN_HEIGHT, WINDOW_TITLE);
	if (!engine->win_ptr)
	{
		report_error("Window creation failed");
		return (0);
	}
	return (1);
}

static int	initialize_world(t_engine *engine, char *map_file)
{
	engine->world = world_create();
	if (!engine->world)
		return (0);
	if (!world_parse_file(engine->world, map_file))
	{
		return (0);
	}
	if (!world_validate(engine->world))
	{
		return (0);
	}
	if (!check_map_closed(engine->world))
	{
		report_error("Map is not closed or surrounded by walls");
		return (0);
	}
	return (1);
}

static int	initialize_character_and_renderer(t_engine *engine)
{
	engine->character = character_allocate();
	if (!engine->character)
		return (0);
	character_initialize_position(engine->character, engine->world);
	engine->renderer = renderer_create(engine->mlx_ptr);
	if (!engine->renderer)
		return (0);
	if (!load_all_textures(engine->renderer, engine->world, engine->mlx_ptr))
		return (report_error("Texture loading failed"));
	if (!load_bonus_textures(engine))
    	return (report_error("Failed to load bonus textures"));
	return (1);
}

int	engine_initialize(t_engine *engine, char *map_file)
{
	if (!engine)
		return (0);
	if (!initialize_world(engine, map_file))
		return (0);
	if (!initialize_mlx(engine))
		return (0);
	if (!initialize_character_and_renderer(engine))
		return (0);
	engine->is_running = 1;
	engine->mouse_enabled = 1;
	engine->key_w = 0;
	engine->key_a = 0;
	engine->key_s = 0;
	engine->key_d = 0;
	engine->key_left = 0;
	engine->key_right = 0;
	setup_event_hooks(engine);
	return (1);
}
