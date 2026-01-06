/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:17:56 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/06 17:25:47 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**load_file_lines(const char *filename)
{
	char	*content;
	char	**lines;

	content = read_file_content(filename);
	if (!content)
		return (NULL);
	if (!validate_map_layout(content))
	{
		safe_free(content);
		return (NULL);
	}
	lines = split_string(content, '\n');
	safe_free(content);
	return (lines);
}

static int	parse_config_line(t_world *world, char *line)
{
	int	tex_res;
	int	col_res;

	tex_res = parse_texture_line(world, line);
	col_res = parse_color_line(world, line);
	if (tex_res < 0 || col_res < 0)
		return (-1);
	if (tex_res == 0 && col_res == 0)
		return (report_error("Invalid line found in map file"), -1);
	return (0);
}

static int	process_lines_and_find_map(t_world *world, char **lines)
{
	int	i;
	int	map_start;

	i = 0;
	map_start = -1;
	while (lines[i])
	{
		if (lines[i][0])
		{
			if (is_map_line(lines[i]))
			{
				if (map_start == -1)
					map_start = i;
			}
			else if (parse_config_line(world, lines[i]) < 0)
				return (-2);
		}
		i++;
	}
	if (map_start == -1)
		return (report_error("No map content found"), -1);
	return (map_start);
}

static int	create_map_grid(t_world *world, char **lines, int start)
{
	parse_map_dimensions(lines, start, world);
	world->grid = safe_calloc(world->height + 1, sizeof(char *));
	if (!world->grid)
		return (0);
	copy_map_data(lines, start, world);
	return (1);
}

int	world_parse_file(t_world *world, const char *filename)
{
	char	**lines;
	int		map_start;

	lines = load_file_lines(filename);
	if (!lines)
		return (0);
	map_start = process_lines_and_find_map(world, lines);
	if (map_start < 0)
	{
		free_string_array(lines);
		return (0);
	}
	if (!create_map_grid(world, lines, map_start))
	{
		free_string_array(lines);
		return (0);
	}
	free_string_array(lines);
	return (1);
}
