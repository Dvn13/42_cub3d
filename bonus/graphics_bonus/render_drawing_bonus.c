/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_drawing_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdivan <mdivan@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 14:01:26 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/03 04:01:10 by mdivan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	calc_texture_x(t_ray *ray, t_texture *texture)
{
	int	tex_x;

	tex_x = (int)(ray->wall_x * (double)texture->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0)
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		tex_x = texture->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	return (tex_x);
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
		engine->renderer->z_buffer[x] = ray.perp_wall_dist;
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
	tex_x = calc_texture_x(ray, texture);
	step = 1.0 * texture->height / ray->line_height;
	tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2 + ray->line_height / 2)
		* step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos & (texture->height - 1);
		tex_pos += step;
		renderer_put_pixel(renderer, x, y, renderer_get_pixel_color(texture,
				tex_x, tex_y));
		y++;
	}
}
