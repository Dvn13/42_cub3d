/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_ceiling_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdivan <mdivan@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 04:02:57 by mdivan            #+#    #+#             */
/*   Updated: 2026/01/03 04:03:01 by mdivan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	render_flat_background(t_engine *engine)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			if (y < SCREEN_HEIGHT / 2)
				renderer_put_pixel(engine->renderer, x, y,
					engine->world->ceiling_color);
			else
				renderer_put_pixel(engine->renderer, x, y,
					engine->world->floor_color);
			x++;
		}
		y++;
	}
}

static void	init_floor_math(t_engine *engine, t_floor *h, int y)
{
	h->ray_dir_x0 = engine->character->dir.x - engine->character->plane.x;
	h->ray_dir_y0 = engine->character->dir.y - engine->character->plane.y;
	h->ray_dir_x1 = engine->character->dir.x + engine->character->plane.x;
	h->ray_dir_y1 = engine->character->dir.y + engine->character->plane.y;
	h->row_dist = (0.5 * SCREEN_HEIGHT) / (y - SCREEN_HEIGHT / 2.0);
	h->step_x = h->row_dist * (h->ray_dir_x1 - h->ray_dir_x0) / SCREEN_WIDTH;
	h->step_y = h->row_dist * (h->ray_dir_y1 - h->ray_dir_y0) / SCREEN_WIDTH;
	h->floor_x = engine->character->pos.x + h->row_dist * h->ray_dir_x0;
	h->floor_y = engine->character->pos.y + h->row_dist * h->ray_dir_y0;
}

static void	draw_floor_scanline(t_engine *engine, t_floor *h, int y)
{
	int	x;
	int	color;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		h->tx = (int)(64 * (h->floor_x - (int)h->floor_x)) & 63;
		h->ty = (int)(64 * (h->floor_y - (int)h->floor_y)) & 63;
		h->floor_x += h->step_x;
		h->floor_y += h->step_y;
		if (engine->renderer->floor_texture)
			color = renderer_get_pixel_color(engine->renderer->floor_texture,
					h->tx, h->ty);
		else
			color = engine->world->floor_color;
		renderer_put_pixel(engine->renderer, x, y, color);
		if (engine->renderer->ceiling_texture)
			color = renderer_get_pixel_color(engine->renderer->ceiling_texture,
					h->tx, h->ty);
		else
			color = engine->world->ceiling_color;
		renderer_put_pixel(engine->renderer, x, SCREEN_HEIGHT - y - 1, color);
		x++;
	}
}

void	render_floor_ceiling(t_engine *engine)
{
	t_floor	h;
	int		y;

	if (!engine || !engine->renderer || !engine->world)
		return ;
	if (!engine->renderer->floor_texture && !engine->renderer->ceiling_texture)
	{
		render_flat_background(engine);
		return ;
	}
	y = SCREEN_HEIGHT / 2;
	while (y < SCREEN_HEIGHT)
	{
		init_floor_math(engine, &h, y);
		draw_floor_scanline(engine, &h, y);
		y++;
	}
}
