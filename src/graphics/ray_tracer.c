#include "cub3d.h"

void	ray_trace_init(t_ray *ray, t_character *character, int screen_x)
{
	if (!ray || !character)
		return ;
	ray->camera_x = 2 * screen_x / (double)SCREEN_WIDTH - 1;
	ray->ray_dir_x = character->dir.x + character->plane.x * ray->camera_x;
	ray->ray_dir_y = character->dir.y + character->plane.y * ray->camera_x;
	ray->map_x = (int)character->pos.x;
	ray->map_y = (int)character->pos.y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

void	ray_trace_perform_dda(t_ray *ray, t_world *world)
{
	if (!ray || !world)
		return ;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (world_is_wall(world, ray->map_x, ray->map_y))
			ray->hit = 1;
	}
}

int	ray_trace_get_texture_index(t_ray *ray)
{
	if (!ray)
		return (0);
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (2);
		else
			return (3);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (1);
		else
			return (0);
	}
}
