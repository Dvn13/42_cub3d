#include "cub3d.h"

t_player	*player_create(void)
{
	t_player	*player;

	player = ft_calloc(1, sizeof(t_player));
	if (!player)
		return (NULL);
	player->pos_x = 0.0;
	player->pos_y = 0.0;
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.0;
	player->spawn_direction = 'N';
	return (player);
}

void	player_set_direction(t_player *player, char direction)
{
	double	fov_radians;

	if (!player)
		return ;
	player->spawn_direction = direction;
	fov_radians = (FOV * M_PI) / 180.0;
	if (direction == 'N')
	{
		player->dir_x = 0.0;
		player->dir_y = -1.0;
		player->plane_x = tan(fov_radians / 2.0);
		player->plane_y = 0.0;
	}
	else if (direction == 'S')
	{
		player->dir_x = 0.0;
		player->dir_y = 1.0;
		player->plane_x = -tan(fov_radians / 2.0);
		player->plane_y = 0.0;
	}
	else if (direction == 'E')
	{
		player->dir_x = 1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = tan(fov_radians / 2.0);
	}
	else if (direction == 'W')
	{
		player->dir_x = -1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = -tan(fov_radians / 2.0);
	}
}

void	player_init_position(t_player *player, t_map *map)
{
	int	i;
	int	j;

	if (!player || !map || !map->grid)
		return ;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] == 'N' || map->grid[i][j] == 'S' || 
				map->grid[i][j] == 'E' || map->grid[i][j] == 'W')
			{
				player->pos_x = (double)j + 0.5;
				player->pos_y = (double)i + 0.5;
				player_set_direction(player, map->grid[i][j]);
				map->grid[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

void	player_destroy(t_player *player)
{
	if (player)
		free(player);
}