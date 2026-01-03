/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdivan <mdivan@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 13:16:59 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/03 04:02:35 by mdivan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	move_with_sliding(t_character *character, t_world *world,
		double move_x, double move_y)
{
	if (!check_wall_collision(character, world, move_x, character->pos.y))
		character->pos.x = move_x;
	if (!check_wall_collision(character, world, character->pos.x, move_y))
		character->pos.y = move_y;
}

void	move_character_forward(t_character *character, t_world *world)
{
	double	new_x;
	double	new_y;

	if (!character || !world)
		return ;
	new_x = character->pos.x + character->dir.x * MOVEMENT_VELOCITY;
	new_y = character->pos.y + character->dir.y * MOVEMENT_VELOCITY;
	move_with_sliding(character, world, new_x, new_y);
}

void	move_character_backward(t_character *character, t_world *world)
{
	double	new_x;
	double	new_y;

	if (!character || !world)
		return ;
	new_x = character->pos.x - character->dir.x * MOVEMENT_VELOCITY;
	new_y = character->pos.y - character->dir.y * MOVEMENT_VELOCITY;
	move_with_sliding(character, world, new_x, new_y);
}

void	move_character_left(t_character *character, t_world *world)
{
	double	new_x;
	double	new_y;

	if (!character || !world)
		return ;
	new_x = character->pos.x + character->dir.y * MOVEMENT_VELOCITY;
	new_y = character->pos.y - character->dir.x * MOVEMENT_VELOCITY;
	move_with_sliding(character, world, new_x, new_y);
}

void	move_character_right(t_character *character, t_world *world)
{
	double	new_x;
	double	new_y;

	if (!character || !world)
		return ;
	new_x = character->pos.x - character->dir.y * MOVEMENT_VELOCITY;
	new_y = character->pos.y + character->dir.x * MOVEMENT_VELOCITY;
	move_with_sliding(character, world, new_x, new_y);
}
