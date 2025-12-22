#include "cub3d.h"

int	engine_main_loop(t_engine *engine)
{
	if (!engine)
		return (0);
	mlx_loop(engine->mlx_ptr);
	return (1);
}

void	engine_update(t_engine *engine)
{
	if (!engine || !engine->is_running)
		return ;
	process_input(engine);
	render_frame(engine);
}

void	engine_shutdown(t_engine *engine)
{
	if (engine)
		engine->is_running = 0;
	mlx_destroy_image(engine->mlx_ptr, engine->renderer->image_ptr);
	mlx_destroy_window(engine->mlx_ptr, engine->win_ptr);
	mlx_destroy_display(engine->mlx_ptr);
	free(engine->mlx_ptr);
	exit(0);
}
