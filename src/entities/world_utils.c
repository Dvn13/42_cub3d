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

int	parse_color_value(char *color_str)
{
	char	**rgb_values;
	int		r;
	int		g;
	int		b;
	int		color;

	rgb_values = split_string(color_str, ',');
	if (!rgb_values || !rgb_values[0] || !rgb_values[1] || !rgb_values[2])
	{
		free_string_array(rgb_values);
		return (-1);
	}
	r = ft_atoi(rgb_values[0]);
	g = ft_atoi(rgb_values[1]);
	b = ft_atoi(rgb_values[2]);
	free_string_array(rgb_values);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	color = (r << 16) | (g << 8) | b;
	return (color);
}

int	is_map_line(char *line)
{
	int	i;

	if (!line || !line[0])
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != ' '
			&& line[i] != '\t' && line[i] != '\n')
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

void	copy_map_data(char **lines, int start_index, t_world *world)
{
	int	i;
	int	j;
	int	line_length;

	i = 0;
	while (i < world->height)
	{
		line_length = string_length(lines[start_index + i]);
		if (lines[start_index + i][line_length - 1] == '\n')
			line_length--;
		world->grid[i] = safe_calloc(world->width + 1, sizeof(char));
		if (!world->grid[i])
			return ;
		j = 0;
		while (j < line_length)
		{
			world->grid[i][j] = lines[start_index + i][j];
			j++;
		}
		while (j < world->width)
		{
			world->grid[i][j] = ' ';
			j++;
		}
		world->grid[i][j] = '\0';
		i++;
	}
	world->grid[i] = NULL; 
}
