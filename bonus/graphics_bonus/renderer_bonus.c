/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:18:25 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/02 17:13:32 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	renderer_put_pixel(t_renderer *renderer, int x, int y, int color)
{
	char	*pixel;

	if (!renderer || !renderer->image_data || x < 0 || y < 0
		|| x >= renderer->image_width || y >= renderer->image_height)
		return ;
	pixel = renderer->image_data + (y * renderer->size_line + x
			* (renderer->bits_per_pixel / 8));
	*(int *)pixel = color;
}

int	renderer_get_pixel_color(t_texture *texture, int x, int y)
{
	char	*pixel;

	if (!texture || !texture->data || x < 0 || y < 0 || x >= texture->width
		|| y >= texture->height)
		return (0);
	pixel = texture->data + (y * texture->size_line + x
			* (texture->bits_per_pixel / 8));
	return (*(int *)pixel);
}

static void	sort_sprites(t_sprite *sprites, int count)
{
	int			i;
	int			j;
	t_sprite	temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (sprites[j].dist < sprites[j + 1].dist)
			{
				temp = sprites[j];
				sprites[j] = sprites[j + 1];
				sprites[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	calc_sprite_transform(t_engine *eng, t_sprite *spr,
				t_spr_calc *calc)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	sprite_x = spr->x - eng->character->pos.x;
	sprite_y = spr->y - eng->character->pos.y;
	inv_det = 1.0 / (eng->character->plane.x * eng->character->dir.y
			- eng->character->dir.x * eng->character->plane.y);
	calc->transform_x = inv_det * (eng->character->dir.y * sprite_x
			- eng->character->dir.x * sprite_y);
	calc->transform_y = inv_det * (-eng->character->plane.y * sprite_x
			+ eng->character->plane.x * sprite_y);
	calc->screen_x = (int)((SCREEN_WIDTH / 2) * (1 + calc->transform_x
				/ calc->transform_y));
}

static void	calc_sprite_dims(t_spr_calc *calc)
{
	calc->height = abs((int)(SCREEN_HEIGHT / calc->transform_y)) / 2;
	calc->draw_start_y = -calc->height / 2 + SCREEN_HEIGHT / 2;
	if (calc->draw_start_y < 0)
		calc->draw_start_y = 0;
	calc->draw_end_y = calc->height / 2 + SCREEN_HEIGHT / 2;
	if (calc->draw_end_y >= SCREEN_HEIGHT)
		calc->draw_end_y = SCREEN_HEIGHT - 1;
	calc->width = abs((int)(SCREEN_HEIGHT / calc->transform_y)) / 2;
	calc->draw_start_x = -calc->width / 2 + calc->screen_x;
	if (calc->draw_start_x < 0)
		calc->draw_start_x = 0;
	calc->draw_end_x = calc->width / 2 + calc->screen_x;
	if (calc->draw_end_x >= SCREEN_WIDTH)
		calc->draw_end_x = SCREEN_WIDTH - 1;
}

static void	draw_sprite_stripe(t_engine *eng, t_spr_calc *spr_calc, int stripe,
	int tex_x)
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

static void	process_sprites(t_engine *eng)
{
	t_spr_calc		spr_calc;
	int				i;
	int				stripe;
	int				tex_x;
	t_texture		*tex;

	i = -1;
	tex = eng->renderer->sprite_textures[eng->world->current_sprite_frame];
	while (++i < eng->world->sprite_count)
	{
		calc_sprite_transform(eng, &eng->world->sprites[i], &spr_calc);
		calc_sprite_dims(&spr_calc);
		stripe = spr_calc.draw_start_x;
		while (stripe < spr_calc.draw_end_x)
		{
			tex_x = (int)(256 * (stripe - (-spr_calc.width / 2 + spr_calc.screen_x))
					* tex->width / spr_calc.width) / 256;
			if (spr_calc.transform_y > 0 && stripe > 0 && stripe < SCREEN_WIDTH
				&& spr_calc.transform_y < eng->renderer->z_buffer[stripe])
				draw_sprite_stripe(eng, &spr_calc, stripe, tex_x);
			stripe++;
		}
	}
}

void	render_sprites(t_engine *engine)
{
	int	i;

	i = 0;
	while (i < engine->world->sprite_count)
	{
		engine->world->sprites[i].dist = ((engine->character->pos.x
					- engine->world->sprites[i].x)
				* (engine->character->pos.x - engine->world->sprites[i].x)
				+ (engine->character->pos.y - engine->world->sprites[i].y)
				* (engine->character->pos.y - engine->world->sprites[i].y));
		i++;
	}
	sort_sprites(engine->world->sprites, engine->world->sprite_count);
	process_sprites(engine);
}

void	render_frame(t_engine *engine)
{
	if (!engine || !engine->renderer || !engine->character || !engine->world)
		return ;
	renderer_clear_screen(engine->renderer, COLOR_BLACK);
	render_floor_ceiling(engine);
	render_walls(engine);
	render_sprites(engine);
	render_minimap(engine);
	renderer_draw_to_window(engine->renderer, engine->mlx_ptr, engine->win_ptr);
}
