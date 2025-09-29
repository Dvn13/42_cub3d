#include "cub3d.h"

int	check_wall_collision(t_character *character, t_world *world, double new_x,
		double new_y)
{
	if (!character || !world)
		return (1);
	if (world_is_wall(world, (int)new_x, (int)character->pos.y))
		return (1);
	if (world_is_wall(world, (int)character->pos.x, (int)new_y))
		return (1);
	return (0);
}
