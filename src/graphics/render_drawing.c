#include "cub3d.h"

void	render_walls(t_engine *engine)
{
	t_ray	ray;
	int		x;

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
		render_vertical_line(engine->renderer, x, &ray,
			engine->renderer->textures[ray_trace_get_texture_index(&ray)]);
		x++;
	}
}

void	render_floor_ceiling(t_engine *engine)
{
	int	x;
	int	y;

	if (!engine || !engine->renderer || !engine->world)
		return ;
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

void	render_vertical_line(t_renderer *renderer, int x, t_ray *ray,
		t_texture *texture)
{
	int	y;
	int	color;

	if (!renderer || !ray || !texture)
		return ;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		ray->texture_x = (int)(ray->wall_x * texture->width);
		if (ray->side == 0 && ray->ray_dir_x > 0)
			ray->texture_x = texture->width - ray->texture_x - 1;
		if (ray->side == 1 && ray->ray_dir_y < 0)
			ray->texture_x = texture->width - ray->texture_x - 1;
		color = renderer_get_pixel_color(texture, ray->texture_x, (int)((y
						- ray->draw_start) * texture->height
					/ ray->line_height));
		renderer_put_pixel(renderer, x, y, color);
		y++;
	}
}
