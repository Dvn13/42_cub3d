/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:18:25 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/02 13:16:19 by gbodur           ###   ########.fr       */
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

void	render_sprites(t_engine *engine)
{
	int			i;
	t_sprite	*sprite;
	double		sprite_x;
	double		sprite_y;
	double		inv_det;
	double		transform_x;
	double		transform_y;
	int			sprite_screen_x;
	int			sprite_height;
	int			draw_start_y;
	int			draw_end_y;
	int			sprite_width;
	int			draw_start_x;
	int			draw_end_x;
	int			stripe;
	int			tex_x;
	int			tex_y;
	int			d;
	int			color;
	int			y;
	t_texture	*tex;

	i = 0;
	while (i < engine->world->sprite_count)
	{
		engine->world->sprites[i].dist = ((engine->character->pos.x
					- engine->world->sprites[i].x) * (engine->character->pos.x
					- engine->world->sprites[i].x) + (engine->character->pos.y
					- engine->world->sprites[i].y) * (engine->character->pos.y
					- engine->world->sprites[i].y));
		i++;
	}
	sort_sprites(engine->world->sprites, engine->world->sprite_count);
	i = 0;
	while (i < engine->world->sprite_count)
	{
		sprite = &engine->world->sprites[i];
		sprite_x = sprite->x - engine->character->pos.x;
		sprite_y = sprite->y - engine->character->pos.y;
		inv_det = 1.0 / (engine->character->plane.x * engine->character->dir.y
				- engine->character->dir.x * engine->character->plane.y);
		transform_x = inv_det * (engine->character->dir.y * sprite_x
				- engine->character->dir.x * sprite_y);
		transform_y = inv_det * (-engine->character->plane.y * sprite_x
				+ engine->character->plane.x * sprite_y);
		sprite_screen_x = (int)((SCREEN_WIDTH / 2) * (1 + transform_x
					/ transform_y));
		sprite_height = abs((int)(SCREEN_HEIGHT / (transform_y))) / 2;
		draw_start_y = -sprite_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_start_y < 0)
			draw_start_y = 0;
		draw_end_y = sprite_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_end_y >= SCREEN_HEIGHT)
			draw_end_y = SCREEN_HEIGHT - 1;
		sprite_width = abs((int)(SCREEN_HEIGHT / (transform_y))) / 2;
		draw_start_x = -sprite_width / 2 + sprite_screen_x;
		if (draw_start_x < 0)
			draw_start_x = 0;
		draw_end_x = sprite_width / 2 + sprite_screen_x;
		if (draw_end_x >= SCREEN_WIDTH)
			draw_end_x = SCREEN_WIDTH - 1;
		stripe = draw_start_x;
		while (stripe < draw_end_x)
		{
			tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x))
					* engine->renderer->sprite_textures[0]->width
					/ sprite_width) / 256;
			if (transform_y > 0 && stripe > 0 && stripe < SCREEN_WIDTH
				&& transform_y < engine->renderer->z_buffer[stripe])
			{
				y = draw_start_y;
				while (y < draw_end_y)
				{
					d = (y)*256 - SCREEN_HEIGHT * 128 + sprite_height * 128;
					tex_y = ((d * engine->renderer->sprite_textures[0]->height)
							/ sprite_height) / 256;
					tex = engine->renderer->sprite_textures[engine->world->current_sprite_frame];
					if (tex)
					{
						color = renderer_get_pixel_color(tex, tex_x, tex_y);
						if ((color & 0x00FFFFFF) != 0)
							renderer_put_pixel(engine->renderer, stripe, y,
								color);
					}
					y++;
				}
			}
			stripe++;
		}
		i++;
	}
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
