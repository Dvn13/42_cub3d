#include "cub3d.h"

static int	validate_arguments(int argc, char **argv)
{
	int	len;

	if (argc != 2)
	{
		write(STDERR_FILENO, "Usage: ./cub3D <map_file.cub>\n", 30);
		return (0);
	}
	len = ft_strlen(argv[1]);
	if (len < 5 || ft_strcmp(&argv[1][len - 4], ".cub") != 0)
	{
		ft_error("Map file must have .cub extension", ERR_INVALID_MAP);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (!validate_arguments(argc, argv))
		return (1);
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		ft_error(NULL, ERR_MALLOC);
	if (!game_init(game, argv[1]))
	{
		ft_cleanup(game);
		return (1);
	}
	game_loop(game);
	ft_cleanup(game);
	return (0);
}