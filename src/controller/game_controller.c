#include "cub3d.h"

int	game_init(t_game *game, char *map_file)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (0);
	game->map = map_create();
	if (!game->map)
		return (0);
	if (!map_parse_file(game->map, map_file))
		return (0);
	if (!map_validate(game->map))
		return (0);
	game->player = player_create();
	if (!game->player)
		return (0);
	player_init_position(game->player, game->map);
	game->renderer = renderer_create(game->mlx_ptr);
	if (!game->renderer)
		return (0);
	if (!load_all_textures(game->renderer, game->map, game->mlx_ptr))
		return (0);
	game->win_ptr = mlx_new_window(game->mlx_ptr, WINDOW_WIDTH, 
		WINDOW_HEIGHT, WINDOW_TITLE);
	if (!game->win_ptr)
		return (0);
	game->running = 1;
	mouse_init();
	smooth_movement_init();
	setup_hooks(game);
	return (1);
}

int	game_loop(t_game *game)
{
	if (!game)
		return (0);
	mlx_loop(game->mlx_ptr);
	return (1);
}

void	game_update(t_game *game)
{
	if (!game || !game->running)
		return ;
	perf_start_frame();
	process_input(game);
	render_frame(game);
	perf_end_frame();
}

void	game_shutdown(t_game *game)
{
	if (!game)
		return ;
	game->running = 0;
}