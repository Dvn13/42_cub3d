/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_drawing_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 14:01:26 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/01 15:22:55 by gbodur           ###   ########.fr       */
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
	t_floor		h;
	int			y;

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

void	render_walls(t_engine *engine)
{
	t_ray		ray;
	t_texture	*tex;
	char		cell_type;
	int			x;

	if (!engine || !engine->character || !engine->world || !engine->renderer)
		return ;
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		ray_trace_init(&ray, engine->character, x);
		ray_trace_calculate_step_and_side_dist(&ray, engine->character);
		ray_trace_perform_dda(&ray, engine->world);
		ray_trace_calculate_wall_distance(&ray, engine->character);
		ray_trace_calculate_draw_limits(&ray);
		ray_trace_calculate_wall_x(&ray, engine->character);
		cell_type = world_get_cell(engine->world, ray.map_x, ray.map_y);
		if (cell_type == 'D')
            tex = engine->renderer->door_texture;
        else
            tex = engine->renderer->textures[ray_trace_get_texture_index(&ray)];
		render_vertical_line(engine->renderer, x, &ray, tex);
		x++;
	}
}

void	render_vertical_line(t_renderer *renderer, int x, t_ray *ray,
		t_texture *texture)
{
	int		y;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;

	if (!renderer || !ray || !texture)
		return ;
	tex_x = (int)(ray->wall_x * (double)texture->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0)
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		tex_x = texture->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	step = 1.0 * texture->height / ray->line_height;
	tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2
			+ ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos & (texture->height - 1);
		tex_pos += step;
		renderer_put_pixel(renderer, x, y,
			renderer_get_pixel_color(texture, tex_x, tex_y));
		y++;
	}
}
