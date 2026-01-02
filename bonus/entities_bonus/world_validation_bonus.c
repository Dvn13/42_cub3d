/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_validation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:43:50 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/02 13:13:53 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	count_map_players(t_world *world)
{
	int	i;
	int	j;

	world->character_count = 0;
	i = 0;
	while (i < world->height)
	{
		j = 0;
		while (world->grid[i][j])
		{
			if (world->grid[i][j] == 'N' || world->grid[i][j] == 'S' ||
				world->grid[i][j] == 'E' || world->grid[i][j] == 'W')
			{
				world->character_count++;
			}
			else if (world->grid[i][j] == SPRITE_CHAR)
			{
				world->sprite_count++;
			}
			j++;
		}
		i++;
	}
}

static int	check_textures_loaded(t_world *world)
{
	if (!world->north_texture_path)
		return (report_error("Missing North texture (NO)"));
	if (!world->south_texture_path)
		return (report_error("Missing South texture (SO)"));
	if (!world->west_texture_path)
		return (report_error("Missing West texture (WE)"));
	if (!world->east_texture_path)
		return (report_error("Missing East texture (EA)"));
	return (1);
}

static int	check_floor_ceiling_set(t_world *world)
{
	if (world->floor_color == -1 && world->floor_texture_path == NULL)
		return (report_error("Missing Floor specification (F: Color or Texture)"));
	if (world->ceiling_color == -1 && world->ceiling_texture_path == NULL)
		return (report_error("Missing Ceiling specification (C: Color or Texture)"));
	return (1);
}

static int	check_player_exists(t_world *world)
{
	if (world->character_count == 0)
		return (report_error("Map missing player start position (N,S,E,W)"));
	if (world->character_count > 1)
		return (report_error("Map has multiple player start positions"));
	return (1);
}

static char	**duplicate_map(t_world *world)
{
	char	**map_copy;
	int		i;

	i = 0;
	map_copy = malloc(sizeof(char *) * (world->height + 1));
	if (!map_copy)
		return (NULL);
	while (i < world->height)
	{
		map_copy[i] = duplicate_string(world->grid[i]);
		if (!map_copy[i])
		{
			free_string_array(map_copy);
			return (NULL);
		}
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

static int	flood_fill(t_world *world, char **map, int x, int y)
{
	int	rows;
	int	cols;

	rows = world->height;
	if (y < 0 || y >= rows || !map[y])
		return (0);
	cols = string_length(map[y]);
	if (x < 0 || x >= cols)
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (1);
	if (map[y][x] == ' ' || map[y][x] == '\t')
		return (0);
	map[y][x] = 'V';
	if (!flood_fill(world, map, x + 1, y))
		return (0);
	if (!flood_fill(world, map, x - 1, y))
		return (0);
	if (!flood_fill(world, map, x, y + 1))
		return (0);
	if (!flood_fill(world, map, x, y - 1))
		return (0);
	return (1);
}

int	check_map_closed(t_world *world)
{
	char	**map_copy;
	int		x;
	int		y;
	int		player_found;

	map_copy = duplicate_map(world);
	if (!map_copy)
		return (0);
	player_found = 0;
	y = 0;
	while (y < world->height && !player_found)
	{
		x = 0;
		while (map_copy[y][x])
		{
			if (map_copy[y][x] == 'N' || map_copy[y][x] == 'S' ||
				map_copy[y][x] == 'E' || map_copy[y][x] == 'W')
			{
				player_found = 1;
				break ;
			}
			x++;
		}
		if (!player_found)
			y++;
	}
	if (!player_found || !flood_fill(world, map_copy, x, y))
	{
		free_string_array(map_copy);
		return (0);
	}
	free_string_array(map_copy);
	return (1);
}

static int	init_sprite_positions(t_world *world)
{
	int	i;
	int	j;
	int	k;

	if (world->sprite_count == 0)
		return (1);
	world->sprites = malloc(sizeof(t_sprite) * world->sprite_count);
	if (!world->sprites)
		return (report_error("Memory allocation for sprites failed"));
	i = 0;
	k = 0;
	while (i < world->height)
	{
		j = 0;
		while (world->grid[i][j])
		{
			if (world->grid[i][j] == SPRITE_CHAR)
			{
				world->sprites[k].x = j + 0.5;
				world->sprites[k].y = i + 0.5;
				world->sprites[k].texture_id = 0;
				world->sprites[k].dist = 0;
				world->grid[i][j] = '0';
				k++;
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	world_validate(t_world *world)
{
	if (!world || !world->grid)
		return (report_error("Map data is missing or empty"));
	count_map_players(world);
	if (!init_sprite_positions(world))
		return (0);
	if (!check_textures_loaded(world))
		return (0);
	if (!check_floor_ceiling_set(world))
		return (0);
	if (!check_player_exists(world))
		return (0);
	if (!check_map_closed(world))
		return (report_error("Map is not closed / surrounded by walls"));	
	return (1);
}
