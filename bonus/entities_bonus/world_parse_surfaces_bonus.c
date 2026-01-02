/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_parse_surfaces_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 19:16:07 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/02 19:17:42 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static char	*trim_space(char *str)
{
	char	*trimmed;
	int		start;
	int		end;
	int		len;

	if (!str)
		return (NULL);
	start = 0;
	while (str[start] && (str[start] == ' ' || str[start] == '\t'
			|| str[start] == '\n'))
		start++;
	end = string_length(str) - 1;
	while (end > start && (str[end] == ' ' || str[end] == '\t'
			|| str[end] == '\n'))
		end--;
	len = end - start + 1;
	trimmed = (char *)malloc(sizeof(char) * (len + 1));
	if (!trimmed)
		return (NULL);
	string_copy(trimmed, str + start, len);
	trimmed[len] = '\0';
	return (trimmed);
}

static int	has_extension(char *str, char *ext)
{
	int	str_len;
	int	ext_len;
	int	i;

	if (!str || !ext)
		return (0);
	str_len = string_length(str);
	ext_len = string_length(ext);
	if (str_len < ext_len)
		return (0);
	i = 0;
	while (str[i])
	{
		if (compare_strings(&str[i], ext) == 0)
			return (1);
		i++;
	}
	if (str_len >= 4 && str[str_len - 4] == '.' && str[str_len - 3] == 'x'
		&& str[str_len - 2] == 'p' && str[str_len - 1] == 'm')
	{
		return (1);
	}
	return (0);
}

static int	assign_texture_data(t_world *world, char type, char *path)
{
	if (type == 'F')
	{
		if (world->floor_texture_path)
			return (0);
		world->floor_texture_path = duplicate_string(path);
	}
	else if (type == 'C')
	{
		if (world->ceiling_texture_path)
			return (0);
		world->ceiling_texture_path = duplicate_string(path);
	}
	return (1);
}

static int	assign_color_data(t_world *world, char type, char *path)
{
	int	color;

	color = parse_color_value(path);
	if (color == -1)
		return (0);
	if (type == 'F')
		world->floor_color = color;
	else
		world->ceiling_color = color;
	return (1);
}

int	parse_color_or_texture(t_world *world, char *line)
{
	char	**tokens;
	char	*val;
	int		res;

	tokens = split_string(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1])
	{
		free_string_array(tokens);
		return (0);
	}
	if (compare_strings(tokens[0], "F") != 0
		&& compare_strings(tokens[0], "C") != 0)
	{
		free_string_array(tokens);
		return (0);
	}
	val = trim_space(tokens[1]);
	if (has_extension(val, ".xpm"))
		res = assign_texture_data(world, tokens[0][0], val);
	else
		res = assign_color_data(world, tokens[0][0], val);
	free(val);
	free_string_array(tokens);
	return (res);
}
