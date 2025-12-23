/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 13:12:14 by gbodur            #+#    #+#             */
/*   Updated: 2025/12/23 13:38:50 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_character_right(t_character *character)
{
	double	old_dir_x;
	double	old_plane_x;

	if (!character)
		return ;
	old_dir_x = character->dir.x;
	old_plane_x = character->plane.x;
	character->dir.x = character->dir.x * cos(ROTATION_VELOCITY)
		- character->dir.y * sin(ROTATION_VELOCITY);
	character->dir.y = old_dir_x * sin(ROTATION_VELOCITY) + character->dir.y
		* cos(ROTATION_VELOCITY);
	character->plane.x = character->plane.x * cos(ROTATION_VELOCITY)
		- character->plane.y * sin(ROTATION_VELOCITY);
	character->plane.y = old_plane_x * sin(ROTATION_VELOCITY)
		+ character->plane.y * cos(ROTATION_VELOCITY);
}

void	rotate_character_left(t_character *character)
{
	double	old_dir_x;
	double	old_plane_x;

	if (!character)
		return ;
	old_dir_x = character->dir.x;
	old_plane_x = character->plane.x;
	character->dir.x = character->dir.x * cos(-ROTATION_VELOCITY)
		- character->dir.y * sin(-ROTATION_VELOCITY);
	character->dir.y = old_dir_x * sin(-ROTATION_VELOCITY) + character->dir.y
		* cos(-ROTATION_VELOCITY);
	character->plane.x = character->plane.x * cos(-ROTATION_VELOCITY)
		- character->plane.y * sin(-ROTATION_VELOCITY);
	character->plane.y = old_plane_x * sin(-ROTATION_VELOCITY)
		+ character->plane.y * cos(-ROTATION_VELOCITY);
}
