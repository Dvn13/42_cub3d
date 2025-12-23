/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 13:04:36 by gbodur            #+#    #+#             */
/*   Updated: 2025/12/23 14:00:16 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_trace_calculate_step_and_side_dist(t_ray *ray,
		t_character *character)
{
	if (!ray || !character)
		return ;
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (character->pos.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - character->pos.x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (character->pos.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - character->pos.y)
			* ray->delta_dist_y;
	}
}

void	ray_trace_calculate_wall_distance(t_ray *ray, t_character *character)
{
	if (!ray || !character)
		return ;
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - character->pos.x + (1 - ray->step_x)
				/ 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - character->pos.y + (1 - ray->step_y)
				/ 2) / ray->ray_dir_y;
	if (ray->perp_wall_dist < 0)
		ray->perp_wall_dist = 0.0001;
}

void	ray_trace_calculate_draw_limits(t_ray *ray)
{
	if (!ray)
		return ;
	ray->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	
	ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_end >= SCREEN_HEIGHT)
		ray->draw_end = SCREEN_HEIGHT - 1;
}

void	ray_trace_calculate_wall_x(t_ray *ray, t_character *character)
{
	if (!ray || !character)
		return ;
	if (ray->side == 0)
		ray->wall_x = character->pos.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = character->pos.x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
}