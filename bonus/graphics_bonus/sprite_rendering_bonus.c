/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_rendering_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 04:03:25 by mdivan            #+#    #+#             */
/*   Updated: 2026/01/04 14:33:34 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_sprites_on_minimap(t_engine *engine)
{
	int			i;
	int			scr_x;
	int			scr_y;
	t_sprite	*sprite;

	i = 0;
	while (i < engine->world->sprite_count)
	{
		sprite = &engine->world->sprites[i];
		if (sprite->is_collected == 0)
		{
			scr_x = MINIMAP_PAD + (int)(sprite->x * MINIMAP_SCALE);
			scr_y = MINIMAP_PAD + (int)(sprite->y * MINIMAP_SCALE);
			renderer_put_pixel(engine->renderer, scr_x, scr_y, 0xFFD700);
			renderer_put_pixel(engine->renderer, scr_x + 1, scr_y, 0xFFD700);
			renderer_put_pixel(engine->renderer, scr_x, scr_y + 1, 0xFFD700);
			renderer_put_pixel(engine->renderer, scr_x + 1, scr_y + 1,
				0xFFD700);
		}
		i++;
	}
}

static void	draw_sprite_stripe(t_engine *eng, t_spr_calc *spr_calc,
	int stripe, int tex_x)
{
	int			y;
	int			d;
	int			tex_y;
	int			color;
	t_texture	*tex;

	y = spr_calc->draw_start_y;
	tex = eng->renderer->sprite_textures[eng->world->current_sprite_frame];
	while (y < spr_calc->draw_end_y)
	{
		d = (y) * 256 - SCREEN_HEIGHT * 128 + spr_calc->height * 128;
		tex_y = ((d * tex->height) / spr_calc->height) / 256;
		color = renderer_get_pixel_color(tex, tex_x, tex_y);
		if ((color & 0x00FFFFFF) != 0)
			renderer_put_pixel(eng->renderer, stripe, y, color);
		y++;
	}
}

static void	process_sprite_loop(t_engine *eng, t_spr_calc *calc,
	t_texture *tex)
{
	int	stripe;
	int	tex_x;

	stripe = calc->draw_start_x;
	while (stripe < calc->draw_end_x)
	{
		tex_x = (int)(256 * (stripe - (-calc->width / 2 + calc->screen_x))
				* tex->width / calc->width) / 256;
		if (calc->transform_y > 0 && stripe > 0 && stripe < SCREEN_WIDTH
			&& calc->transform_y < eng->renderer->z_buffer[stripe])
			draw_sprite_stripe(eng, calc, stripe, tex_x);
		stripe++;
	}
}

static void	process_sprites(t_engine *engine)
{
	t_spr_calc	spr_calc;
	int			i;
	int			frame;
	t_texture	*tex;

	i = -1;
	frame = engine->world->current_sprite_frame;
	tex = engine->renderer->sprite_textures[frame];
	while (++i < engine->world->sprite_count)
	{
		if (engine->world->sprites[i].is_collected)
			continue ;
		calc_sprite_transform(engine, &engine->world->sprites[i], &spr_calc);
		calc_sprite_dims(&spr_calc);
		process_sprite_loop(engine, &spr_calc, tex);
	}
}

void	render_sprites(t_engine *engine)
{
	calculate_sprite_distances(engine);
	sort_sprites(engine->world->sprites, engine->world->sprite_count);
	process_sprites(engine);
}
