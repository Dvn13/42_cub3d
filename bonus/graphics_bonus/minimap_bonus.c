/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 16:04:29 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/04 13:37:18 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_minimap_line(t_engine *engine, int x1, int y1, int x2, int y2)
{
	double	delta_x;
	double	delta_y;
	double	steps;
	double	x;
	double	y;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	if (fabs(delta_x) > fabs(delta_y))
		steps = fabs(delta_x);
	else
		steps = fabs(delta_y);
	delta_x /= steps;
	delta_y /= steps;
	x = x1;
	y = y1;
	while (steps >= 0)
	{
		if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
			renderer_put_pixel(engine->renderer, (int)x, (int)y, 0xFF0000);
		x += delta_x;
		y += delta_y;
		steps--;
	}
}

static void	draw_player_direction(t_engine *engine)
{
	int	center_x;
	int	center_y;
	int	end_x;
	int	end_y;
	int	line_len;

	line_len = MINIMAP_SCALE * 2;
	center_x = MINIMAP_PAD + (int)(engine->character->pos.x * MINIMAP_SCALE);
	center_y = MINIMAP_PAD + (int)(engine->character->pos.y * MINIMAP_SCALE);
	end_x = center_x + (int)(engine->character->dir.x * line_len);
	end_y = center_y + (int)(engine->character->dir.y * line_len);
	draw_minimap_line(engine, center_x, center_y, end_x, end_y);
}

static void	draw_minimap_square(t_engine *engine, int x, int y, int color)
{
	int	i;
	int	j;
	int	pixel_x;
	int	pixel_y;

	i = 0;
	while (i < MINIMAP_SCALE)
	{
		j = 0;
		while (j < MINIMAP_SCALE)
		{
			pixel_x = MINIMAP_PAD + (x * MINIMAP_SCALE) + j;
			pixel_y = MINIMAP_PAD + (y * MINIMAP_SCALE) + i;
			if (pixel_x < SCREEN_WIDTH && pixel_y < SCREEN_HEIGHT)
			{
				renderer_put_pixel(engine->renderer, pixel_x, pixel_y, color);
			}
			j++;
		}
		i++;
	}
}

static void	draw_player_on_minimap(t_engine *engine)
{
	int	center_x;
	int	center_y;
	int	i;
	int	j;

	center_x = MINIMAP_PAD + (int)(engine->character->pos.x * MINIMAP_SCALE);
	center_y = MINIMAP_PAD + (int)(engine->character->pos.y * MINIMAP_SCALE);
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			if ((center_x + j) < SCREEN_WIDTH
				&& (center_y + i) < SCREEN_HEIGHT)
				renderer_put_pixel(engine->renderer, center_x + j,
					center_y + i, COLOR_PLAYER);
			j++;
		}
		i++;
	}
}

void	render_minimap(t_engine *engine)
{
	int		x;
	int		y;
	char	cell;

	y = 0;
	while (y < engine->world->height)
	{
		x = 0;
		while (x < engine->world->width)
		{
			if (x < string_length(engine->world->grid[y]))
			{
				cell = engine->world->grid[y][x];
				if (cell == WALL_SYMBOL)
					draw_minimap_square(engine, x, y, COLOR_WALL);
				else if (cell != ' ' && cell != '\n')
					draw_minimap_square(engine, x, y, COLOR_FLOOR);
			}
			x++;
		}
		y++;
	}
	draw_player_on_minimap(engine);
	draw_player_direction(engine);
}
