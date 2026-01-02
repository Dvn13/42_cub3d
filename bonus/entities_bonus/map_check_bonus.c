/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 19:23:03 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/02 19:24:51 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_map_line(char *line)
{
	int	i;

	if (!line || !line[0])
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != 'D' && line[i] != 'O' && line[i] != ' '
			&& line[i] != '\n' && line[i] != SPRITE_CHAR)
			return (0);
		i++;
	}
	return (1);
}

void	parse_map_dimensions(char **lines, int start_index, t_world *world)
{
	int	i;
	int	current_width;

	world->height = 0;
	world->width = 0;
	i = start_index;
	while (lines[i])
	{
		if (is_map_line(lines[i]))
		{
			current_width = string_length(lines[i]);
			if (lines[i][current_width - 1] == '\n')
				current_width--;
			if (current_width > world->width)
				world->width = current_width;
			world->height++;
		}
		i++;
	}
}

static int	fill_single_row(t_world *world, char *line, int i)
{
	int	j;
	int	len;

	len = string_length(line);
	if (line[len - 1] == '\n')
		len--;
	world->grid[i] = safe_calloc(world->width + 1, sizeof(char));
	if (!world->grid[i])
		return (0);
	j = 0;
	while (j < len)
	{
		world->grid[i][j] = line[j];
		j++;
	}
	while (j < world->width)
	{
		world->grid[i][j] = ' ';
		j++;
	}
	world->grid[i][j] = '\0';
	return (1);
}

void	copy_map_data(char **lines, int start_index, t_world *world)
{
	int	i;

	i = 0;
	while (i < world->height)
	{
		if (!fill_single_row(world, lines[start_index + i], i))
			return ;
		i++;
	}
	world->grid[i] = NULL;
}
