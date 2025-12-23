/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 13:16:59 by gbodur            #+#    #+#             */
/*   Updated: 2025/12/23 13:41:30 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	move_character_forward(t_character *character, t_world *world)
{
	double	new_x;
	double	new_y;

	if (!character || !world)
		return ;
	new_x = character->pos.x + character->dir.x * MOVEMENT_VELOCITY;
	new_y = character->pos.y + character->dir.y * MOVEMENT_VELOCITY;
	if (!check_wall_collision(character, world, new_x, new_y))
	{
		character->pos.x = new_x;
		character->pos.y = new_y;
	}
}

void	move_character_backward(t_character *character, t_world *world)
{
	double	new_x;
	double	new_y;

	if (!character || !world)
		return ;
	new_x = character->pos.x - character->dir.x * MOVEMENT_VELOCITY;
	new_y = character->pos.y - character->dir.y * MOVEMENT_VELOCITY;
	if (!check_wall_collision(character, world, new_x, new_y))
	{
		character->pos.x = new_x;
		character->pos.y = new_y;
	}
}

void	move_character_left(t_character *character, t_world *world)
{
	double	new_x;
	double	new_y;

	if (!character || !world)
		return ;
	new_x = character->pos.x + character->dir.y * MOVEMENT_VELOCITY;
	new_y = character->pos.y - character->dir.x * MOVEMENT_VELOCITY;
	if (!check_wall_collision(character, world, new_x, new_y))
	{
		character->pos.x = new_x;
		character->pos.y = new_y;
	}
}

void	move_character_right(t_character *character, t_world *world)
{
	double	new_x;
	double	new_y;

	if (!character || !world)
		return ;
	new_x = character->pos.x - character->dir.y * MOVEMENT_VELOCITY;
	new_y = character->pos.y + character->dir.x * MOVEMENT_VELOCITY;
	if (!check_wall_collision(character, world, new_x, new_y))
	{
		character->pos.x = new_x;
		character->pos.y = new_y;
	}
}
