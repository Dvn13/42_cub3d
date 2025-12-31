/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 15:34:59 by gbodur            #+#    #+#             */
/*   Updated: 2025/12/31 20:57:15 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	validate_command_line_arguments(int argc, char **argv)
{
	int	length;

	if (argc != 2)
	{
		write(STDERR_FILENO, "Error!\nUsage: ./cub3D <map_file.cub>\n", 38);
		return (0);
	}
	length = string_length(argv[1]);
	if (length < 5 || compare_strings(&argv[1][length - 4], ".cub") != 0
		|| (length >= 5 && argv[1][length - 5] == '/'))
	{
		error_handler("Map file must have a name and .cub extension",
			ERR_INVALID_MAP);
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
		return(report_error("Memory allocation failed"));
	if (!engine_initialize(engine, argv[1]))
	{
		cleanup_engine(engine);
		return (1);
	}
	engine_main_loop(engine);
	cleanup_engine(engine);
	return (0);
}
