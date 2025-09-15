#include "cub3d.h"

#define MINIMAP_SIZE 200
#define MINIMAP_SCALE 10
#define MINIMAP_X 20
#define MINIMAP_Y 20

static void	draw_minimap_background(t_renderer *renderer)
{
	int	x;
	int	y;

	y = MINIMAP_Y;
	while (y < MINIMAP_Y + MINIMAP_SIZE)
	{
		x = MINIMAP_X;
		while (x < MINIMAP_X + MINIMAP_SIZE)
		{
			renderer_put_pixel(renderer, x, y, 0x333333);
			x++;
		}
		y++;
	}
}

static void	draw_minimap_walls(t_renderer *renderer, t_map *map)
{
	int	map_x;
	int	map_y;
	int	pixel_x;
	int	pixel_y;
	int	i;
	int	j;

	map_y = 0;
	while (map_y < map->height && map_y * MINIMAP_SCALE < MINIMAP_SIZE)
	{
		map_x = 0;
		while (map_x < map->width && map_x * MINIMAP_SCALE < MINIMAP_SIZE)
		{
			if (map_is_wall(map, map_x, map_y))
			{
				pixel_y = MINIMAP_Y + map_y * MINIMAP_SCALE;
				i = 0;
				while (i < MINIMAP_SCALE && pixel_y + i < MINIMAP_Y + MINIMAP_SIZE)
				{
					pixel_x = MINIMAP_X + map_x * MINIMAP_SCALE;
					j = 0;
					while (j < MINIMAP_SCALE && pixel_x + j < MINIMAP_X + MINIMAP_SIZE)
					{
						renderer_put_pixel(renderer, pixel_x + j, pixel_y + i, COLOR_WHITE);
						j++;
					}
					i++;
				}
			}
			map_x++;
		}
		map_y++;
	}
}

static void	draw_player_on_minimap(t_renderer *renderer, t_player *player)
{
	int		player_x;
	int		player_y;
	int		i;
	int		j;
	double	dir_end_x;
	double	dir_end_y;

	player_x = MINIMAP_X + (int)(player->pos_x * MINIMAP_SCALE);
	player_y = MINIMAP_Y + (int)(player->pos_y * MINIMAP_SCALE);
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			if (player_x + j >= MINIMAP_X && player_x + j < MINIMAP_X + MINIMAP_SIZE &&
				player_y + i >= MINIMAP_Y && player_y + i < MINIMAP_Y + MINIMAP_SIZE)
				renderer_put_pixel(renderer, player_x + j, player_y + i, COLOR_RED);
			j++;
		}
		i++;
	}
	dir_end_x = player_x + player->dir_x * 15;
	dir_end_y = player_y + player->dir_y * 15;
	draw_line(renderer, player_x, player_y, (int)dir_end_x, (int)dir_end_y, COLOR_RED);
}

void	draw_line(t_renderer *renderer, int x0, int y0, int x1, int y1, int color)
{
	int	dx;
	int	dy;
	int	err;
	int	e2;
	int	sx;
	int	sy;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	sx = (x0 < x1) ? 1 : -1;
	sy = (y0 < y1) ? 1 : -1;
	err = dx - dy;
	while (1)
	{
		if (x0 >= MINIMAP_X && x0 < MINIMAP_X + MINIMAP_SIZE &&
			y0 >= MINIMAP_Y && y0 < MINIMAP_Y + MINIMAP_SIZE)
			renderer_put_pixel(renderer, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	render_minimap(t_game *game)
{
	draw_minimap_background(game->renderer);
	draw_minimap_walls(game->renderer, game->map);
	draw_player_on_minimap(game->renderer, game->player);
}