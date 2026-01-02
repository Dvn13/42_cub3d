/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_layout.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 18:23:52 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/02 18:37:51 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static int	check_line_empty(char *line)
{
	int	j;

	j = 0;
	while (line[j] && line[j] != '\n')
	{
		if (line[j] != ' ' && line[j] != '\t' && line[j] != '\r')
			return (0);
		j++;
	}
	return (1);
}

static int	check_row_state(char *content, int i, int *started, int *gap)
{
	if (check_line_empty(&content[i]))
	{
		if (*started)
			*gap = 1;
	}
	else if (!is_config_line(content, i))
	{
		if (*gap)
			return (report_error("Map cannot be separated by empty lines"));
		*started = 1;
	}
	else if (*started)
		return (report_error("Map content must be the last element"));
	return (1);
}

int	validate_map_layout(char *content)
{
	int	i;
	int	map_started;
	int	gap_detected;

	i = 0;
	map_started = 0;
	gap_detected = 0;
	while (content[i])
	{
		if (!check_row_state(content, i, &map_started, &gap_detected))
			return (0);
		while (content[i] && content[i] != '\n')
			i++;
		if (content[i] == '\n')
			i++;
	}
	if (!map_started)
		return (report_error("No map content found"));
	return (1);
}
