#include "cub3d.h"

#define MOUSE_SENSITIVITY 0.002
#define MOUSE_THRESHOLD 5

typedef struct s_mouse_state
{
	int		last_x;
	int		last_y;
	int		is_initialized;
	int		mouse_enabled;
}	t_mouse_state;

static t_mouse_state	g_mouse = {0};

void	mouse_init(void)
{
	g_mouse.last_x = WINDOW_WIDTH / 2;
	g_mouse.last_y = WINDOW_HEIGHT / 2;
	g_mouse.is_initialized = 0;
	g_mouse.mouse_enabled = 1;
}

void	mouse_toggle(void)
{
	g_mouse.mouse_enabled = !g_mouse.mouse_enabled;
}

int	mouse_is_enabled(void)
{
	return (g_mouse.mouse_enabled);
}

static void	rotate_player_by_angle(t_player *player, double angle)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos_angle - player->dir_y * sin_angle;
	player->dir_y = old_dir_x * sin_angle + player->dir_y * cos_angle;
	player->plane_x = player->plane_x * cos_angle - player->plane_y * sin_angle;
	player->plane_y = old_plane_x * sin_angle + player->plane_y * cos_angle;
}

int	handle_mouse_move(int x, int y, t_game *game)
{
	int		delta_x;
	double	rotation_angle;

	if (!g_mouse.mouse_enabled || !game || !game->player)
		return (0);
	if (!g_mouse.is_initialized)
	{
		g_mouse.last_x = x;
		g_mouse.last_y = y;
		g_mouse.is_initialized = 1;
		return (0);
	}
	delta_x = x - g_mouse.last_x;
	if (abs(delta_x) < MOUSE_THRESHOLD)
	{
		g_mouse.last_x = x;
		g_mouse.last_y = y;
		return (0);
	}
	rotation_angle = delta_x * MOUSE_SENSITIVITY;
	rotate_player_by_angle(game->player, rotation_angle);
	g_mouse.last_x = x;
	g_mouse.last_y = y;
	return (0);
}

int	handle_mouse_click(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	(void)game;
	if (button == 1)
	{
		mouse_toggle();
		return (0);
	}
	return (0);
}