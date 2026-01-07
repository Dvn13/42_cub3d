/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:17:24 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/07 16:58:33 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	calculate_minimap_scale(t_engine *engine)
{
	int	scale_x;
	int	scale_y;
	int	scale;

	scale_x = MINIMAP_MAX_SIZE / engine->world->width;
	scale_y = MINIMAP_MAX_SIZE / engine->world->height;
	if (scale_x < scale_y)
		scale = scale_x;
	else
		scale = scale_y;
	if (scale < 1)
		scale = 1;
	if (scale > MINIMAP_SCALE)
		scale = MINIMAP_SCALE;
	return (scale);
}

void	draw_minimap_line(t_engine *engine, int *coords)
{
	double	delta_x;
	double	delta_y;
	double	steps;
	double	x;
	double	y;

	delta_x = coords[2] - coords[0];
	delta_y = coords[3] - coords[1];
	if (fabs(delta_x) > fabs(delta_y))
		steps = fabs(delta_x);
	else
		steps = fabs(delta_y);
	delta_x /= steps;
	delta_y /= steps;
	x = coords[0];
	y = coords[1];
	while (steps >= 0)
	{
		if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
			renderer_put_pixel(engine->renderer, (int)x, (int)y, 0xFF0000);
		x += delta_x;
		y += delta_y;
		steps--;
	}
}

void	draw_minimap_square(t_engine *engine, int x, int y, int color)
{
	int	i;
	int	j;
	int	pixel_x;
	int	pixel_y;
	int	scale;

	scale = calculate_minimap_scale(engine);
	i = 0;
	while (i < scale)
	{
		j = 0;
		while (j < scale)
		{
			pixel_x = MINIMAP_PAD + (x * scale) + j;
			pixel_y = MINIMAP_PAD + (y * scale) + i;
			if (pixel_x < SCREEN_WIDTH && pixel_y < SCREEN_HEIGHT)
			{
				renderer_put_pixel(engine->renderer, pixel_x, pixel_y, color);
			}
			j++;
		}
		i++;
	}
}

void	draw_sprites_on_minimap(t_engine *engine)
{
	int			i;
	int			scr_x;
	int			scr_y;
	int			scale;
	t_sprite	*sprite;

	scale = calculate_minimap_scale_for_sprite(engine);
	i = 0;
	while (i < engine->world->sprite_count)
	{
		sprite = &engine->world->sprites[i];
		if (sprite->is_collected == 0)
		{
			scr_x = MINIMAP_PAD + (int)(sprite->x * scale);
			scr_y = MINIMAP_PAD + (int)(sprite->y * scale);
			renderer_put_pixel(engine->renderer, scr_x, scr_y, 0xFFD700);
			renderer_put_pixel(engine->renderer, scr_x + 1, scr_y, 0xFFD700);
			renderer_put_pixel(engine->renderer, scr_x, scr_y + 1, 0xFFD700);
			renderer_put_pixel(engine->renderer, scr_x + 1, scr_y + 1,
				0xFFD700);
		}
		i++;
	}
}
