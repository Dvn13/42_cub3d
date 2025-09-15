#include "cub3d.h"

int	check_wall_collision(t_player *player, t_map *map, double new_x, double new_y)
{
	(void)player;
	if (map_is_wall(map, (int)new_x, (int)new_y))
		return (1);
	return (0);
}

void	move_player_forward(t_player *player, t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x + player->dir_x * MOVEMENT_SPEED;
	new_y = player->pos_y + player->dir_y * MOVEMENT_SPEED;
	if (!check_wall_collision(player, map, new_x, player->pos_y))
		player->pos_x = new_x;
	if (!check_wall_collision(player, map, player->pos_x, new_y))
		player->pos_y = new_y;
}

void	move_player_backward(t_player *player, t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x - player->dir_x * MOVEMENT_SPEED;
	new_y = player->pos_y - player->dir_y * MOVEMENT_SPEED;
	if (!check_wall_collision(player, map, new_x, player->pos_y))
		player->pos_x = new_x;
	if (!check_wall_collision(player, map, player->pos_x, new_y))
		player->pos_y = new_y;
}

void	move_player_left(t_player *player, t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x - player->plane_x * MOVEMENT_SPEED;
	new_y = player->pos_y - player->plane_y * MOVEMENT_SPEED;
	if (!check_wall_collision(player, map, new_x, player->pos_y))
		player->pos_x = new_x;
	if (!check_wall_collision(player, map, player->pos_x, new_y))
		player->pos_y = new_y;
}

void	move_player_right(t_player *player, t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x + player->plane_x * MOVEMENT_SPEED;
	new_y = player->pos_y + player->plane_y * MOVEMENT_SPEED;
	if (!check_wall_collision(player, map, new_x, player->pos_y))
		player->pos_x = new_x;
	if (!check_wall_collision(player, map, player->pos_x, new_y))
		player->pos_y = new_y;
}

void	rotate_player_left(t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(-ROTATION_SPEED) - 
		player->dir_y * sin(-ROTATION_SPEED);
	player->dir_y = old_dir_x * sin(-ROTATION_SPEED) + 
		player->dir_y * cos(-ROTATION_SPEED);
	player->plane_x = player->plane_x * cos(-ROTATION_SPEED) - 
		player->plane_y * sin(-ROTATION_SPEED);
	player->plane_y = old_plane_x * sin(-ROTATION_SPEED) + 
		player->plane_y * cos(-ROTATION_SPEED);
}

void	rotate_player_right(t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(ROTATION_SPEED) - 
		player->dir_y * sin(ROTATION_SPEED);
	player->dir_y = old_dir_x * sin(ROTATION_SPEED) + 
		player->dir_y * cos(ROTATION_SPEED);
	player->plane_x = player->plane_x * cos(ROTATION_SPEED) - 
		player->plane_y * sin(ROTATION_SPEED);
	player->plane_y = old_plane_x * sin(ROTATION_SPEED) + 
		player->plane_y * cos(ROTATION_SPEED);
}