/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdivan <mdivan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 15:34:59 by gbodur            #+#    #+#             */
/*   Updated: 2025/12/22 23:49:20 by mdivan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	validate_command_line_arguments(int argc, char **argv)
{
	int	length;

	if (argc != 2)
	{
		write(STDERR_FILENO, "Usage: ./cub3D <map_file.cub>\n", 32);
		return (0);
	}
	length = string_length(argv[1]);
	if (length < 5 || compare_strings(&argv[1][length - 4], ".cub") != 0)
	{
		error_handler("Map file must have .cub extension", ERR_INVALID_MAP);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_engine	*engine;

	if (!validate_command_line_arguments(argc, argv))
		return (1);
	engine = safe_calloc(1, sizeof(t_engine));
	if (!engine)
		error_handler(NULL, ERR_MEMORY_ALLOC);
	if (!engine_initialize(engine, argv[1]))
	{
		cleanup_engine(engine);
		return (1);
	}
	engine_main_loop(engine);
	cleanup_engine(engine);
	return (0); 
}
