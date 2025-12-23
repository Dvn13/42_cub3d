/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 13:15:32 by gbodur            #+#    #+#             */
/*   Updated: 2025/12/23 14:22:47 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_wall_collision(t_character *character, t_world *world, double new_x,
		double new_y)
{
	if (!character || !world)
		return (1);
	if (world_is_wall(world, (int)(new_x + COLLISION_BUFFER),
		(int)(new_y + COLLISION_BUFFER)))
		return (1);
	if (world_is_wall(world, (int)(new_x - COLLISION_BUFFER),
		(int)(new_y + COLLISION_BUFFER)))
		return (1);
	if (world_is_wall(world, (int)(new_x + COLLISION_BUFFER),
		(int)(new_y - COLLISION_BUFFER)))
		return (1);
	if (world_is_wall(world, (int)(new_x - COLLISION_BUFFER),
		(int)(new_y - COLLISION_BUFFER)))
		return (1);
	return (0);
}
