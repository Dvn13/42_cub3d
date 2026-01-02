/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:18:44 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/02 17:57:16 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	if (!str)
		return (0);
	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\f' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

static int	count_commas(const char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

static int	is_str_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			while (str[i] && (str[i] == ' ' || str[i] == '\t'))
				i++;
			if (str[i] != '\0')
				return (0);
			break ;
		}
		i++;
	}
	return (1);
}

static int	get_rgb_result(char **rgb)
{
	int	r;
	int	g;
	int	b;

	if (!is_str_digit(rgb[0]) || !is_str_digit(rgb[1])
		|| !is_str_digit(rgb[2]))
		return (-1);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

int	parse_color_value(char *color_str)
{
	char	**rgb_values;
	int		color;

	if (count_commas(color_str) != 2)
		return (-1);
	rgb_values = split_string(color_str, ',');
	if (!rgb_values)
		return (-1);
	if (!rgb_values[0] || !rgb_values[1] || !rgb_values[2] || rgb_values[3])
	{
		free_string_array(rgb_values);
		return (-1);
	}
	color = get_rgb_result(rgb_values);
	free_string_array(rgb_values);
	return (color);
}
