/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:17:56 by gbodur            #+#    #+#             */
/*   Updated: 2025/12/23 19:02:35 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*read_file_content(const char *filename)
{
	int		fd;
	char	*content;
	char	*temp;
	int		bytes_read;
	char	buffer[1024];

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		error_handler(strerror(errno), ERR_INVALID_MAP);
		return (NULL);
	}
	content = duplicate_string("");
	if (!content)
	{
		close(fd);
		return (NULL);
	}
	while ((bytes_read = read(fd, buffer, 1023)) > 0)
	{
		buffer[bytes_read] = '\0';
		temp = join_strings(content, buffer);
		safe_free(content);
		if (!temp)
		{
			close(fd);
			return (NULL);
		}
		content = temp;
	}
	close(fd);
	return (content);
}

static int	parse_texture_line(t_world *world, char *line)
{
	char	**tokens;

	tokens = split_string(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1])
	{
		free_string_array(tokens);
		return (0);
	}
	if (compare_strings(tokens[0], "NO") == 0)
	{
		if (world->north_texture_path)
		{
			error_handler("Duplicate texture (NO)", 2);
			free_string_array(tokens);
			return (0);
		}
		world->north_texture_path = duplicate_string(tokens[1]);
	}
	else if (compare_strings(tokens[0], "SO") == 0)
	{
		if (world->south_texture_path)
		{
			error_handler("Duplicate texture (SO)", 2);
			free_string_array(tokens);
			return (0);
		}
		world->south_texture_path = duplicate_string(tokens[1]);
	}
	else if (compare_strings(tokens[0], "WE") == 0)
	{
		if (world->west_texture_path)
		{
			error_handler("Duplicate texture (WE)", 2);
			free_string_array(tokens);
			return (0);
		}
		world->west_texture_path = duplicate_string(tokens[1]);
	}
	else if (compare_strings(tokens[0], "EA") == 0)
	{
		if (world->east_texture_path)
		{
			error_handler("Duplicate texture (EA)", 2);
			free_string_array(tokens);
			return (0);
		}	
		world->east_texture_path = duplicate_string(tokens[1]);
	}
	else
	{
		free_string_array(tokens);
		return (0);
	}
	free_string_array(tokens);
	return (1);
}

static int	parse_color_line(t_world *world, char *line)
{
	char	**tokens;
	int		color;

	tokens = split_string(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1])
	{
		free_string_array(tokens);
		return (0);
	}
	if (compare_strings(tokens[0], "F") == 0 && world->floor_color != -1)
	{
		error_handler("Duplicate color (F)", 2);
		free_string_array(tokens);
		return (0);
	}
	if (compare_strings(tokens[0], "C") == 0 && world->ceiling_color != -1)
	{
		error_handler("Duplicate color (C)", 2);
		free_string_array(tokens);
		return (0);
	}
	color = parse_color_value(tokens[1]);
	if (color == -1)
	{
		free_string_array(tokens);
		return (0);
	}
	if (compare_strings(tokens[0], "F") == 0)
		world->floor_color = color;
	else if (compare_strings(tokens[0], "C") == 0)
		world->ceiling_color = color;
	else
	{
		free_string_array(tokens);
		return (0);
	}
	free_string_array(tokens);
	return (1);
}

int	world_parse_file(t_world *world, const char *filename)
{
	char	*content;
	char	**lines;
	int		i;
	int		map_start;

	content = read_file_content(filename);
	if (!content)
		return (0);
	lines = split_string(content, '\n');
	safe_free(content);
	if (!lines)
		return (0);
	i = 0;
	map_start = -1;
	while (lines[i])
	{
		if (lines[i][0] && !is_map_line(lines[i]))
		{
			if (!parse_texture_line(world, lines[i]) && !parse_color_line(world,
					lines[i]))
			{
				free_string_array(lines);
				return (0);
			}
		}
		else if (is_map_line(lines[i]) && map_start == -1)
			map_start = i;
		i++;
	}
	if (map_start == -1)
	{
		free_string_array(lines);
		return (0);
	}
	parse_map_dimensions(lines, map_start, world);
	world->grid = safe_calloc(world->height + 1, sizeof(char *));
	if (!world->grid)
	{
		free_string_array(lines);
		return (0);
	}
	copy_map_data(lines, map_start, world);
	free_string_array(lines);
	return (1);
}
