/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdivan <mdivan@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:19:06 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/03 04:00:49 by mdivan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	engine_main_loop(t_engine *engine)
{
	if (!engine)
		return (0);
	mlx_loop(engine->mlx_ptr);
	return (1);
}

static void	update_sprites(t_engine *engine)
{
	static int	frame_counter = 0;
	t_world		*frame;

	if (!engine || !engine->world)
		return ;
	frame_counter++;
	if (frame_counter >= 15)
	{
		frame = engine->world;
		frame->current_sprite_frame = (frame->current_sprite_frame + 1) % 10;
		frame_counter = 0;
	}
}

void	engine_update(t_engine *engine)
{
	if (!engine || !engine->is_running)
		return ;
	process_input(engine);
	update_sprites(engine);
	render_frame(engine);
}

void	engine_shutdown(t_engine *engine)
{
	if (!engine)
		return ;
	engine->is_running = 0;
	cleanup_engine(engine);
	exit(0);
}
