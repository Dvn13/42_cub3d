/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdivan <mdivan@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 04:03:36 by mdivan            #+#    #+#             */
/*   Updated: 2026/01/03 04:03:37 by mdivan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	sort_sprites(t_sprite *sprites, int count)
{
	int			i;
	int			j;
	t_sprite	temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (sprites[j].dist < sprites[j + 1].dist)
			{
				temp = sprites[j];
				sprites[j] = sprites[j + 1];
				sprites[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	calculate_sprite_distances(t_engine *engine)
{
	int	i;

	i = 0;
	while (i < engine->world->sprite_count)
	{
		engine->world->sprites[i].dist = ((engine->character->pos.x
					- engine->world->sprites[i].x)
				* (engine->character->pos.x - engine->world->sprites[i].x)
				+ (engine->character->pos.y - engine->world->sprites[i].y)
				* (engine->character->pos.y - engine->world->sprites[i].y));
		i++;
	}
}

void	calc_sprite_transform(t_engine *eng, t_sprite *spr,
				t_spr_calc *calc)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	sprite_x = spr->x - eng->character->pos.x;
	sprite_y = spr->y - eng->character->pos.y;
	inv_det = 1.0 / (eng->character->plane.x * eng->character->dir.y
			- eng->character->dir.x * eng->character->plane.y);
	calc->transform_x = inv_det * (eng->character->dir.y * sprite_x
			- eng->character->dir.x * sprite_y);
	calc->transform_y = inv_det * (-eng->character->plane.y * sprite_x
			+ eng->character->plane.x * sprite_y);
	calc->screen_x = (int)((SCREEN_WIDTH / 2) * (1 + calc->transform_x
				/ calc->transform_y));
}

void	calc_sprite_dims(t_spr_calc *calc)
{
	calc->height = abs((int)(SCREEN_HEIGHT / calc->transform_y)) / 2;
	calc->draw_start_y = -calc->height / 2 + SCREEN_HEIGHT / 2;
	if (calc->draw_start_y < 0)
		calc->draw_start_y = 0;
	calc->draw_end_y = calc->height / 2 + SCREEN_HEIGHT / 2;
	if (calc->draw_end_y >= SCREEN_HEIGHT)
		calc->draw_end_y = SCREEN_HEIGHT - 1;
	calc->width = abs((int)(SCREEN_HEIGHT / calc->transform_y)) / 2;
	calc->draw_start_x = -calc->width / 2 + calc->screen_x;
	if (calc->draw_start_x < 0)
		calc->draw_start_x = 0;
	calc->draw_end_x = calc->width / 2 + calc->screen_x;
	if (calc->draw_end_x >= SCREEN_WIDTH)
		calc->draw_end_x = SCREEN_WIDTH - 1;
}
