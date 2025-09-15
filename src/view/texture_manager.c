#include "cub3d.h"

void	render_frame(t_game *game)
{
	if (!game || !game->renderer)
		return ;
	render_optimized_floor_ceiling(game);
	render_walls(game);
	render_minimap(game);
	render_fps_display(game->renderer);
	renderer_draw_to_window(game->renderer, game->mlx_ptr, game->win_ptr);
}

void	render_walls(t_game *game)
{
	t_ray		ray;
	int			x;
	int			tex_index;
	t_texture	*current_texture;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		raycast_init(&ray, game->player, x);
		raycast_calculate_step_and_side_dist(&ray, game->player);
		raycast_perform_dda(&ray, game->map);
		raycast_calculate_wall_distance(&ray, game->player);
		raycast_calculate_draw_limits(&ray);
		tex_index = raycast_get_texture_index(&ray);
		current_texture = game->renderer->textures[tex_index];
		if (current_texture)
			calculate_texture_coordinates(&ray, game->player, current_texture);
		render_vertical_line(game->renderer, x, &ray, current_texture);
		x++;
	}
}

void	render_floor_ceiling(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT / 2)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			renderer_put_pixel(game->renderer, x, y, game->map->ceiling_color);
			x++;
		}
		y++;
	}
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			renderer_put_pixel(game->renderer, x, y, game->map->floor_color);
			x++;
		}
		y++;
	}
}

void	render_vertical_line(t_renderer *renderer, int x, t_ray *ray, t_texture *texture)
{
	int		y;
	int		color;
	int		tex_y;
	double	step;
	double	tex_pos;

	if (!texture)
	{
		color = COLOR_RED;
		if (ray->side == 1)
			color = color / 2;
		y = ray->draw_start;
		while (y <= ray->draw_end)
		{
			renderer_put_pixel(renderer, x, y, color);
			y++;
		}
		return ;
	}
	step = 1.0 * texture->height / ray->line_height;
	tex_pos = (ray->draw_start - WINDOW_HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos & (texture->height - 1);
		tex_pos += step;
		color = renderer_get_pixel_color(texture, ray->tex_x, tex_y);
		if (ray->side == 1)
			color = (color >> 1) & 8355711;
		renderer_put_pixel(renderer, x, y, color);
		y++;
	}
}

int	raycast_get_texture_index(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (0);
		else
			return (1);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (2);
		else
			return (3);
	}
}

int	load_all_textures(t_renderer *renderer, t_map *map, void *mlx_ptr)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		renderer->textures[i] = texture_create();
		if (!renderer->textures[i])
			return (0);
		i++;
	}
	if (!texture_load(renderer->textures[0], mlx_ptr, map->east_texture) ||
		!texture_load(renderer->textures[1], mlx_ptr, map->west_texture) ||
		!texture_load(renderer->textures[2], mlx_ptr, map->south_texture) ||
		!texture_load(renderer->textures[3], mlx_ptr, map->north_texture))
		return (0);
	return (1);
}

void	calculate_texture_coordinates(t_ray *ray, t_player *player, t_texture *texture)
{
	if (ray->side == 0)
		ray->wall_x = player->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = player->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)texture->width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = texture->width - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = texture->width - ray->tex_x - 1;
}