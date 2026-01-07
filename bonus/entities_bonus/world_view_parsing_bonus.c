/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_view_parsing_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 19:08:36 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/07 11:29:28 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	set_texture_path(char **dest, char *path, char *err_msg)
{
	if (*dest)
		return (report_error(err_msg));
	*dest = duplicate_string(path);
	return (1);
}

static int	dispatch_texture(t_world *world, char *type, char *path)
{
	if (compare_strings(type, "NO") == 0)
		return (set_texture_path(&world->north_texture_path, path,
				"Duplicate texture (NO)"));
	else if (compare_strings(type, "SO") == 0)
		return (set_texture_path(&world->south_texture_path, path,
				"Duplicate texture (SO)"));
	else if (compare_strings(type, "WE") == 0)
		return (set_texture_path(&world->west_texture_path, path,
				"Duplicate texture (WE)"));
	else if (compare_strings(type, "EA") == 0)
		return (set_texture_path(&world->east_texture_path, path,
				"Duplicate texture (EA)"));
	else if (compare_strings(type, "DO") == 0
		|| compare_strings(type, "D") == 0)
		return (set_texture_path(&world->door_texture_path, path,
				"Duplicate texture (DO)"));
	return (0);
}

int	parse_texture_line(t_world *world, char *line)
{
	char	**tokens;
	int		result;

	tokens = split_string(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1] || tokens[2])
	{
		free_string_array(tokens);
		return (0);
	}
	result = dispatch_texture(world, tokens[0], tokens[1]);
	free_string_array(tokens);
	return (result);
}
