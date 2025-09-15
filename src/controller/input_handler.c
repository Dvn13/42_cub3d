#include "cub3d.h"

static t_input	g_input = {0};
static int		g_keys_pressed[7] = {0};

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_W)
	{
		g_input.key_w = 1;
		g_keys_pressed[0] = 1;
	}
	else if (keycode == KEY_S)
	{
		g_input.key_s = 1;
		g_keys_pressed[1] = 1;
	}
	else if (keycode == KEY_A)
	{
		g_input.key_a = 1;
		g_keys_pressed[2] = 1;
	}
	else if (keycode == KEY_D)
	{
		g_input.key_d = 1;
		g_keys_pressed[3] = 1;
	}
	else if (keycode == KEY_LEFT)
	{
		g_input.key_left = 1;
		g_keys_pressed[4] = 1;
	}
	else if (keycode == KEY_RIGHT)
	{
		g_input.key_right = 1;
		g_keys_pressed[5] = 1;
	}
	else if (keycode == KEY_ESC)
	{
		game_shutdown(game);
		exit(0);
	}
	return (0);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	(void)game;
	if (keycode == KEY_W)
	{
		g_input.key_w = 0;
		g_keys_pressed[0] = 0;
	}
	else if (keycode == KEY_S)
	{
		g_input.key_s = 0;
		g_keys_pressed[1] = 0;
	}
	else if (keycode == KEY_A)
	{
		g_input.key_a = 0;
		g_keys_pressed[2] = 0;
	}
	else if (keycode == KEY_D)
	{
		g_input.key_d = 0;
		g_keys_pressed[3] = 0;
	}
	else if (keycode == KEY_LEFT)
	{
		g_input.key_left = 0;
		g_keys_pressed[4] = 0;
	}
	else if (keycode == KEY_RIGHT)
	{
		g_input.key_right = 0;
		g_keys_pressed[5] = 0;
	}
	return (0);
}

int	handle_window_close(t_game *game)
{
	game_shutdown(game);
	exit(0);
	return (0);
}

void	process_input(t_game *game)
{
	smooth_movement_update(game->player, game->map, g_keys_pressed);
}

int	main_loop_hook(t_game *game)
{
	if (!game || !game->running)
		return (0);
	game_update(game);
	return (0);
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->win_ptr, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->win_ptr, 3, 1L << 1, handle_keyrelease, game);
	mlx_hook(game->win_ptr, 4, 1L << 2, handle_mouse_click, game);
	mlx_hook(game->win_ptr, 6, 1L << 6, handle_mouse_move, game);
	mlx_hook(game->win_ptr, 17, 1L << 17, handle_window_close, game);
	mlx_loop_hook(game->mlx_ptr, main_loop_hook, game);
}