/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_view_parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 18:18:15 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/07 11:29:25 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	set_single_texture(char **dest, char *path, char *err)
{
	if (*dest)
		return (report_error(err), -1);
	*dest = duplicate_string(path);
	return (1);
}

static int	set_texture_path(t_world *world, char *type, char *path)
{
	if (compare_strings(type, "NO") == 0)
		return (set_single_texture(&world->north_texture_path, path,
				"Duplicate texture (NO)"));
	else if (compare_strings(type, "SO") == 0)
		return (set_single_texture(&world->south_texture_path, path,
				"Duplicate texture (SO)"));
	else if (compare_strings(type, "WE") == 0)
		return (set_single_texture(&world->west_texture_path, path,
				"Duplicate texture (WE)"));
	else if (compare_strings(type, "EA") == 0)
		return (set_single_texture(&world->east_texture_path, path,
				"Duplicate texture (EA)"));
	return (0);
}

int	parse_texture_line(t_world *world, char *line)
{
	char	**tokens;
	int		res;

	tokens = split_string(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1] || tokens[2])
	{
		free_string_array(tokens);
		return (0);
	}
	res = set_texture_path(world, tokens[0], tokens[1]);
	free_string_array(tokens);
	return (res);
}

static int	process_color_tokens(t_world *world, char **tokens)
{
	int	color;

	if (compare_strings(tokens[0], "F") == 0 && world->floor_color != -1)
		return (report_error("Duplicate color (F)"), -1);
	if (compare_strings(tokens[0], "C") == 0 && world->ceiling_color != -1)
		return (report_error("Duplicate color (C)"), -1);
	color = parse_color_value(tokens[1]);
	if (color == -1)
		return (0);
	if (compare_strings(tokens[0], "F") == 0)
		world->floor_color = color;
	else if (compare_strings(tokens[0], "C") == 0)
		world->ceiling_color = color;
	else
		return (0);
	return (1);
}

int	parse_color_line(t_world *world, char *line)
{
	char	**tokens;
	int		result;

	tokens = split_string(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1] || tokens[2])
	{
		free_string_array(tokens);
		return (0);
	}
	result = process_color_tokens(world, tokens);
	free_string_array(tokens);
	return (result);
}
