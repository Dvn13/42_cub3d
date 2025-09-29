#include "cub3d.h"

void	error_handler(char *message, int error_code)
{
	if (message)
		write(STDERR_FILENO, message, string_length(message));
	write(STDERR_FILENO, "\n", 1);
	exit(error_code);
}

void	cleanup_engine(t_engine *engine)
{
	if (!engine)
		return ;
	if (engine->world)
		world_destroy(engine->world);
	if (engine->character)
		character_destroy(engine->character);
	if (engine->renderer)
		renderer_destroy(engine->renderer, engine->mlx_ptr);
	if (engine->win_ptr)
		mlx_destroy_window(engine->mlx_ptr, engine->win_ptr);
	if (engine->mlx_ptr)
		free(engine->mlx_ptr);
	safe_free(engine);
}
