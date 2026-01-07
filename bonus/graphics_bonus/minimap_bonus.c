/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 16:04:29 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/07 17:02:07 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_player_direction(t_engine *engine)
{
	int	coords[4];
	int	line_len;
	int	scale;

	scale = calculate_minimap_scale(engine);
	line_len = scale * 2;
	coords[0] = MINIMAP_PAD + (int)(engine->character->pos.x * scale);
	coords[1] = MINIMAP_PAD + (int)(engine->character->pos.y * scale);
	coords[2] = coords[0] + (int)(engine->character->dir.x * line_len);
	coords[3] = coords[1] + (int)(engine->character->dir.y * line_len);
	draw_minimap_line(engine, coords);
}

static void	draw_player_on_minimap(t_engine *engine)
{
	int	center_x;
	int	center_y;
	int	i;
	int	j;
	int	scale;

	scale = calculate_minimap_scale(engine);
	center_x = MINIMAP_PAD + (int)(engine->character->pos.x * scale);
	center_y = MINIMAP_PAD + (int)(engine->character->pos.y * scale);
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
	draw_sprites_on_minimap(engine);
	draw_player_on_minimap(engine);
	draw_player_direction(engine);
}
