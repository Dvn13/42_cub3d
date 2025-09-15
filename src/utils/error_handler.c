#include "cub3d.h"

static const char	*g_error_messages[] = {
	"Success",
	"Memory allocation failed",
	"Failed to open file",
	"Invalid map configuration",
	"MLX initialization failed",
	"Texture loading failed"
};

void	ft_error(char *message, int error_code)
{
	write(STDERR_FILENO, "Error\n", 6);
	if (message)
	{
		write(STDERR_FILENO, message, ft_strlen(message));
		write(STDERR_FILENO, "\n", 1);
	}
	else if (error_code > 0 && error_code < 6)
	{
		write(STDERR_FILENO, g_error_messages[error_code], 
			ft_strlen(g_error_messages[error_code]));
		write(STDERR_FILENO, "\n", 1);
	}
	exit(error_code);
}

void	ft_cleanup(t_game *game)
{
	if (!game)
		return ;
	if (game->renderer)
		renderer_destroy(game->renderer, game->mlx_ptr);
	if (game->map)
		map_destroy(game->map);
	if (game->player)
		player_destroy(game->player);
	if (game->win_ptr && game->mlx_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	free(game);
}