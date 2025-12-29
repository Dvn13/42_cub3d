/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:17:56 by gbodur            #+#    #+#             */
/*   Updated: 2025/12/29 18:14:59 by gbodur           ###   ########.fr       */
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
		report_error(strerror(errno));
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

static int	is_config_line(char *str, int i)
{
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (!str[i] || str[i] == '\n')
		return (0);
	if (str[i] == 'N' || str[i] == 'S' || str[i] == 'W' || str[i] == 'E'
		|| str[i] == 'F' || str[i] == 'C')
		return (1);
	return (0);
}

static int	validate_map_layout(char *content)
{
	int	i;
	int	map_started;
	int	gap_detected;
	int	is_empty;
	int	j;

	i = 0;
	map_started = 0;
	gap_detected = 0;
	while (content[i])
	{
		is_empty = 1;
		j = i;
		while (content[j] && content[j] != '\n')
		{
			if (content[j] != ' ' && content[j] != '\t' && content[j] != '\r')
				is_empty = 0;
			j++;
		}
		if (is_empty)
		{
			if (map_started)
				gap_detected = 1;
		}
		else if (is_config_line(content, i))
		{
			if (map_started)
			{
				report_error("Map content must be the last element in file");
				return (0);
			}
		}
		else
		{
			if (gap_detected)
			{
				report_error("Map cannot be separated by empty lines");
				return (0);
			}
			map_started = 1;
		}
		i = j;
		if (content[i] == '\n')
			i++;
	}
	if (!map_started)
	{
		report_error("No map content found");
		return (0);
	}
	return (1);
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
			free_string_array(tokens);
			report_error("Duplicate texture (NO)");
			return (0);
		}
		world->north_texture_path = duplicate_string(tokens[1]);
	}
	else if (compare_strings(tokens[0], "SO") == 0)
	{
		if (world->south_texture_path)
		{
			free_string_array(tokens);
			report_error("Duplicate texture (SO)");
			return (0);
		}
		world->south_texture_path = duplicate_string(tokens[1]);
	}
	else if (compare_strings(tokens[0], "WE") == 0)
	{
		if (world->west_texture_path)
		{
			free_string_array(tokens);
			report_error("Duplicate texture (WE)");
			return (0);
		}
		world->west_texture_path = duplicate_string(tokens[1]);
	}
	else if (compare_strings(tokens[0], "EA") == 0)
	{
		if (world->east_texture_path)
		{
			free_string_array(tokens);
			report_error("Duplicate texture (EA)");
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
	if (!validate_map_layout(content))
	{
		safe_free(content);
		return (0);
	}

	lines = split_string(content, '\n');
	safe_free(content);
	if (!lines)
		return (0);
	i = 0;
	map_start = -1;
	while (lines[i])
	{
		if (!lines[i][0])
		{
			i++;
			continue;
		}
		
		if (is_map_line(lines[i]))
		{
			if (map_start == -1)
				map_start = i;
		}
		else
		{
			if (!parse_texture_line(world, lines[i]) && !parse_color_line(world, lines[i]))
			{
				free_string_array(lines);
				report_error("Invalid line or character found in map file");
				return (0);
			}
		}
		i++;
	}

	if (map_start == -1)
	{
		free_string_array(lines);
		report_error("No map content found");
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
