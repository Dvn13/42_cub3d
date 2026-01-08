/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_connection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdivan <mdivan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:11:23 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/08 19:33:24 by mdivan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	**type_converter(char **map)
{
	int		**board;
	int		y;
	size_t	len;

	y = 0;
	while (map[y])
		y++;
	board = malloc(sizeof(int *) * (y + 1));
	if (!board)
		return (NULL);
	y = -1;
	while (map[++y])
	{
		len = string_length(map[y]);
		board[y] = safe_calloc(len, sizeof(int));
		if (!board[y])
		{
			while (y--)
				free(board[y]);
			free(board);
			return (NULL);
		}
	}
	board[y] = NULL;
	return (board);
}

static void	recursive_check(char **map, int y, int x, int **visited)
{
	if (y < 0 || x < 0 || !map[y] || !map[y][x])
		return ;
	if (map[y][x] == ' ' || visited[y][x])
		return ;
	visited[y][x] = 'F';
	recursive_check(map, y + 1, x, visited);
	recursive_check(map, y - 1, x, visited);
	recursive_check(map, y, x + 1, visited);
	recursive_check(map, y, x - 1, visited);
}

int	check_space_map(t_world *world)
{
	int	x;
	int	y;
	int	**board;

	board = type_converter(world->grid);
	if (!board)
		return (0);
	recursive_check(world->grid, world->py, world->px, board);
	y = -1;
	while (world->grid[++y])
	{
		x = 0;
		while (world->grid[y][x])
		{
			if ((world->grid[y][x] == 'N' || world->grid[y][x] == 'S'
					|| world->grid[y][x] == 'W' || world->grid[y][x] == 'E'
					|| world->grid[y][x] == '0' || world->grid[y][x] == '1')
				&& !board[y][x])
				return (free_string_array((char **)board), 0);
			x++;
		}
	}
	free_string_array((char **)board);
	return (1);
}
