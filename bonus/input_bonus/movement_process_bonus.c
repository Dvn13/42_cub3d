/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_process_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 04:03:47 by mdivan            #+#    #+#             */
/*   Updated: 2026/01/04 14:30:34 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	process_input(t_engine *engine)
{
	if (!engine || !engine->character || !engine->world)
		return ;
	if (engine->key_w)
		move_character_forward(engine->character, engine->world);
	if (engine->key_s)
		move_character_backward(engine->character, engine->world);
	if (engine->key_a)
		move_character_left(engine->character, engine->world);
	if (engine->key_d)
		move_character_right(engine->character, engine->world);
	if (engine->key_left)
		rotate_character_left(engine->character);
	if (engine->key_right)
		rotate_character_right(engine->character);
}

void	check_sprite_collection(t_engine *engine)
{
	int			i;
	double		dist;
	t_sprite	*sprite;

	if (!engine || !engine->world || !engine->world->sprites)
		return ;
	i = 0;
	while (i < engine->world->sprite_count)
	{
		sprite = &engine->world->sprites[i];
		if (sprite->is_collected == 0)
		{
			dist = sqrt(pow(engine->character->pos.x - sprite->x, 2)
					+ pow(engine->character->pos.y - sprite->y, 2));
			if (dist < 0.5)
				sprite->is_collected = 1;
		}
		i++;
	}
}
