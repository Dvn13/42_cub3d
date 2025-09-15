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
		return (NULL);
	content = ft_strdup("");
	if (!content)
	{
		close(fd);
		return (NULL);
	}
	while ((bytes_read = read(fd, buffer, 1023)) > 0)
	{
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(content, buffer);
		free(content);
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

static int	parse_texture_line(t_map *map, char *line)
{
	char	**tokens;
	
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1])
	{
		free_string_array(tokens);
		return (0);
	}
	if (ft_strcmp(tokens[0], "NO") == 0)
		map->north_texture = ft_strdup(tokens[1]);
	else if (ft_strcmp(tokens[0], "SO") == 0)
		map->south_texture = ft_strdup(tokens[1]);
	else if (ft_strcmp(tokens[0], "WE") == 0)
		map->west_texture = ft_strdup(tokens[1]);
	else if (ft_strcmp(tokens[0], "EA") == 0)
		map->east_texture = ft_strdup(tokens[1]);
	else
	{
		free_string_array(tokens);
		return (0);
	}
	free_string_array(tokens);
	return (1);
}

static int	parse_color_value(char *color_str)
{
	char	**rgb_values;
	int		r;
	int		g;
	int		b;
	int		color;

	rgb_values = ft_split(color_str, ',');
	if (!rgb_values || !rgb_values[0] || !rgb_values[1] || !rgb_values[2])
	{
		free_string_array(rgb_values);
		return (-1);
	}
	r = atoi(rgb_values[0]);
	g = atoi(rgb_values[1]);
	b = atoi(rgb_values[2]);
	free_string_array(rgb_values);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	color = (r << 16) | (g << 8) | b;
	return (color);
}

static int	parse_color_line(t_map *map, char *line)
{
	char	**tokens;
	int		color;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1])
	{
		free_string_array(tokens);
		return (0);
	}
	color = parse_color_value(tokens[1]);
	if (color == -1)
	{
		free_string_array(tokens);
		return (0);
	}
	if (ft_strcmp(tokens[0], "F") == 0)
		map->floor_color = color;
	else if (ft_strcmp(tokens[0], "C") == 0)
		map->ceiling_color = color;
	else
	{
		free_string_array(tokens);
		return (0);
	}
	free_string_array(tokens);
	return (1);
}

static int	is_map_line(char *line)
{
	int	i;

	if (!line || !line[0])
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && 
			line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && 
			line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

static void	parse_map_dimensions(char **lines, int start_index, t_map *map)
{
	int	i;
	int	current_width;

	map->height = 0;
	map->width = 0;
	i = start_index;
	while (lines[i])
	{
		if (is_map_line(lines[i]))
		{
			current_width = ft_strlen(lines[i]);
			if (lines[i][current_width - 1] == '\n')
				current_width--;
			if (current_width > map->width)
				map->width = current_width;
			map->height++;
		}
		i++;
	}
}

static void	copy_map_data(char **lines, int start_index, t_map *map)
{
	int	i;
	int	map_row;
	int	j;
	int	line_len;

	i = start_index;
	map_row = 0;
	while (lines[i] && map_row < map->height)
	{
		if (is_map_line(lines[i]))
		{
			line_len = ft_strlen(lines[i]);
			if (lines[i][line_len - 1] == '\n')
				line_len--;
			map->grid[map_row] = malloc(sizeof(char) * (map->width + 1));
			if (!map->grid[map_row])
				return ;
			j = 0;
			while (j < line_len && j < map->width)
			{
				map->grid[map_row][j] = lines[i][j];
				j++;
			}
			while (j < map->width)
			{
				map->grid[map_row][j] = ' ';
				j++;
			}
			map->grid[map_row][map->width] = '\0';
			map_row++;
		}
		i++;
	}
}

t_map	*map_create(void)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->north_texture = NULL;
	map->south_texture = NULL;
	map->east_texture = NULL;
	map->west_texture = NULL;
	map->floor_color = -1;
	map->ceiling_color = -1;
	map->player_count = 0;
	return (map);
}

int	map_parse_file(t_map *map, const char *filename)
{
	char	*content;
	char	**lines;
	int		i;
	int		map_start;

	content = read_file_content(filename);
	if (!content)
		return (0);
	lines = ft_split(content, '\n');
	free(content);
	if (!lines)
		return (0);
	i = 0;
	map_start = -1;
	while (lines[i])
	{
		if (lines[i][0] && !is_map_line(lines[i]))
		{
			if (!parse_texture_line(map, lines[i]) && 
				!parse_color_line(map, lines[i]))
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
	parse_map_dimensions(lines, map_start, map);
	map->grid = ft_calloc(map->height, sizeof(char *));
	if (!map->grid)
	{
		free_string_array(lines);
		return (0);
	}
	copy_map_data(lines, map_start, map);
	free_string_array(lines);
	return (1);
}

void	map_destroy(t_map *map)
{
	if (!map)
		return ;
	if (map->grid)
		free_string_array(map->grid);
	if (map->north_texture)
		free(map->north_texture);
	if (map->south_texture)
		free(map->south_texture);
	if (map->east_texture)
		free(map->east_texture);
	if (map->west_texture)
		free(map->west_texture);
	free(map);
}