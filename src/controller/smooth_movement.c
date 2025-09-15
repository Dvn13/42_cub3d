#include "cub3d.h"
#include <sys/time.h>

#define ACCELERATION 0.001
#define DECELERATION 0.995
#define MAX_VELOCITY 0.08

typedef struct s_smooth_state
{
	double	velocity_forward;
	double	velocity_backward;
	double	velocity_left;
	double	velocity_right;
	double	rotation_velocity_left;
	double	rotation_velocity_right;
	struct timeval	last_update;
}	t_smooth_state;

static t_smooth_state	g_smooth = {0};

void	smooth_movement_init(void)
{
	g_smooth.velocity_forward = 0.0;
	g_smooth.velocity_backward = 0.0;
	g_smooth.velocity_left = 0.0;
	g_smooth.velocity_right = 0.0;
	g_smooth.rotation_velocity_left = 0.0;
	g_smooth.rotation_velocity_right = 0.0;
	gettimeofday(&g_smooth.last_update, NULL);
}

static double	calculate_delta_time(void)
{
	struct timeval	current_time;
	double			delta_time;

	gettimeofday(&current_time, NULL);
	delta_time = (current_time.tv_sec - g_smooth.last_update.tv_sec) * 1000.0;
	delta_time += (current_time.tv_usec - g_smooth.last_update.tv_usec) / 1000.0;
	g_smooth.last_update = current_time;
	return (delta_time);
}

static void	apply_smooth_forward_movement(t_player *player, t_map *map, double delta_time)
{
	double	new_x;
	double	new_y;
	double	movement_amount;

	movement_amount = g_smooth.velocity_forward * delta_time;
	new_x = player->pos_x + player->dir_x * movement_amount;
	new_y = player->pos_y + player->dir_y * movement_amount;
	if (!check_wall_collision(player, map, new_x, player->pos_y))
		player->pos_x = new_x;
	if (!check_wall_collision(player, map, player->pos_x, new_y))
		player->pos_y = new_y;
}

static void	apply_smooth_backward_movement(t_player *player, t_map *map, double delta_time)
{
	double	new_x;
	double	new_y;
	double	movement_amount;

	movement_amount = g_smooth.velocity_backward * delta_time;
	new_x = player->pos_x - player->dir_x * movement_amount;
	new_y = player->pos_y - player->dir_y * movement_amount;
	if (!check_wall_collision(player, map, new_x, player->pos_y))
		player->pos_x = new_x;
	if (!check_wall_collision(player, map, player->pos_x, new_y))
		player->pos_y = new_y;
}

static void	apply_smooth_strafe_movement(t_player *player, t_map *map, double delta_time)
{
	double	new_x;
	double	new_y;
	double	strafe_amount;

	strafe_amount = (g_smooth.velocity_right - g_smooth.velocity_left) * delta_time;
	new_x = player->pos_x + player->plane_x * strafe_amount;
	new_y = player->pos_y + player->plane_y * strafe_amount;
	if (!check_wall_collision(player, map, new_x, player->pos_y))
		player->pos_x = new_x;
	if (!check_wall_collision(player, map, player->pos_x, new_y))
		player->pos_y = new_y;
}

static void	apply_smooth_rotation(t_player *player, double delta_time)
{
	double	rotation_amount;
	double	old_dir_x;
	double	old_plane_x;
	double	cos_rot;
	double	sin_rot;

	rotation_amount = (g_smooth.rotation_velocity_right - g_smooth.rotation_velocity_left) * delta_time;
	if (fabs(rotation_amount) < 0.001)
		return ;
	cos_rot = cos(rotation_amount);
	sin_rot = sin(rotation_amount);
	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos_rot - player->dir_y * sin_rot;
	player->dir_y = old_dir_x * sin_rot + player->dir_y * cos_rot;
	player->plane_x = player->plane_x * cos_rot - player->plane_y * sin_rot;
	player->plane_y = old_plane_x * sin_rot + player->plane_y * cos_rot;
}

void	smooth_movement_update(t_player *player, t_map *map, int keys_pressed[7])
{
	double	delta_time;

	delta_time = calculate_delta_time();
	if (keys_pressed[0])
		g_smooth.velocity_forward = fmin(g_smooth.velocity_forward + ACCELERATION * delta_time, MAX_VELOCITY);
	else
		g_smooth.velocity_forward *= DECELERATION;
	if (keys_pressed[1])
		g_smooth.velocity_backward = fmin(g_smooth.velocity_backward + ACCELERATION * delta_time, MAX_VELOCITY);
	else
		g_smooth.velocity_backward *= DECELERATION;
	if (keys_pressed[2])
		g_smooth.velocity_left = fmin(g_smooth.velocity_left + ACCELERATION * delta_time, MAX_VELOCITY);
	else
		g_smooth.velocity_left *= DECELERATION;
	if (keys_pressed[3])
		g_smooth.velocity_right = fmin(g_smooth.velocity_right + ACCELERATION * delta_time, MAX_VELOCITY);
	else
		g_smooth.velocity_right *= DECELERATION;
	if (keys_pressed[4])
		g_smooth.rotation_velocity_left = fmin(g_smooth.rotation_velocity_left + ACCELERATION * delta_time * 5, MAX_VELOCITY * 3);
	else
		g_smooth.rotation_velocity_left *= DECELERATION;
	if (keys_pressed[5])
		g_smooth.rotation_velocity_right = fmin(g_smooth.rotation_velocity_right + ACCELERATION * delta_time * 5, MAX_VELOCITY * 3);
	else
		g_smooth.rotation_velocity_right *= DECELERATION;
	apply_smooth_forward_movement(player, map, delta_time);
	apply_smooth_backward_movement(player, map, delta_time);
	apply_smooth_strafe_movement(player, map, delta_time);
	apply_smooth_rotation(player, delta_time);
}