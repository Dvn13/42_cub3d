#include "cub3d.h"

static void	render_floor_line(t_game *game, int y)
{
	int		x;
	double	ray_dir_x0;
	double	ray_dir_y0;
	double	ray_dir_x1;
	double	ray_dir_y1;
	double	pos_z;
	double	row_distance;
	double	floor_step_x;
	double	floor_step_y;
	double	floor_x;
	double	floor_y;

	ray_dir_x0 = game->player->dir_x - game->player->plane_x;
	ray_dir_y0 = game->player->dir_y - game->player->plane_y;
	ray_dir_x1 = game->player->dir_x + game->player->plane_x;
	ray_dir_y1 = game->player->dir_y + game->player->plane_y;
	pos_z = 0.5 * WINDOW_HEIGHT;
	row_distance = pos_z / (y - WINDOW_HEIGHT / 2);
	floor_step_x = row_distance * (ray_dir_x1 - ray_dir_x0) / WINDOW_WIDTH;
	floor_step_y = row_distance * (ray_dir_y1 - ray_dir_y0) / WINDOW_WIDTH;
	floor_x = game->player->pos_x + row_distance * ray_dir_x0;
	floor_y = game->player->pos_y + row_distance * ray_dir_y0;
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		renderer_put_pixel(game->renderer, x, y, game->map->floor_color);
		floor_x += floor_step_x;
		floor_y += floor_step_y;
		x++;
	}
}

static void	render_ceiling_line(t_game *game, int y)
{
	int	x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		renderer_put_pixel(game->renderer, x, y, game->map->ceiling_color);
		x++;
	}
}

void	render_advanced_floor_ceiling(t_game *game)
{
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT / 2)
	{
		render_ceiling_line(game, y);
		y++;
	}
	while (y < WINDOW_HEIGHT)
	{
		render_floor_line(game, y);
		y++;
	}
}

void	render_optimized_floor_ceiling(t_game *game)
{
	char	*pixel;
	int		ceiling_color;
	int		floor_color;
	int		y;
	int		x;
	int		pixel_index;

	ceiling_color = game->map->ceiling_color;
	floor_color = game->map->floor_color;
	y = 0;
	while (y < WINDOW_HEIGHT / 2)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			pixel_index = y * game->renderer->size_line + x * (game->renderer->bpp / 8);
			pixel = game->renderer->img_data + pixel_index;
			*(unsigned int *)pixel = ceiling_color;
			x++;
		}
		y++;
	}
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			pixel_index = y * game->renderer->size_line + x * (game->renderer->bpp / 8);
			pixel = game->renderer->img_data + pixel_index;
			*(unsigned int *)pixel = floor_color;
			x++;
		}
		y++;
	}
}