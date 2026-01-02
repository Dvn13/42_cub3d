/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:27:07 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/02 18:56:54 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_character	*character_allocate(void)
{
	t_character	*character;

	character = safe_calloc(1, sizeof(t_character));
	if (!character)
		return (NULL);
	character->pos.x = 0.0;
	character->pos.y = 0.0;
	character->dir.x = 0.0;
	character->dir.y = 0.0;
	character->plane.x = 0.0;
	character->plane.y = 0.0;
	character->spawn_orientation = 'N';
	return (character);
}

static void	set_east_west_orientation(t_character *character, char orientation,
	double plane_len)
{
	if (orientation == 'E')
	{
		character->dir.x = 1.0;
		character->dir.y = 0.0;
		character->plane.x = 0.0;
		character->plane.y = plane_len;
	}
	else if (orientation == 'W')
	{
		character->dir.x = -1.0;
		character->dir.y = 0.0;
		character->plane.x = 0.0;
		character->plane.y = -plane_len;
	}
}

void	character_set_orientation(t_character *character, char orientation)
{
	double	fov_radians;
	double	plane_len;

	if (!character)
		return ;
	character->spawn_orientation = orientation;
	fov_radians = (FIELD_OF_VIEW * M_PI) / 180.0;
	plane_len = tan(fov_radians / 2.0);
	if (orientation == 'N')
	{
		character->dir.x = 0.0;
		character->dir.y = -1.0;
		character->plane.x = plane_len;
		character->plane.y = 0.0;
	}
	else if (orientation == 'S')
	{
		character->dir.x = 0.0;
		character->dir.y = 1.0;
		character->plane.x = -plane_len;
		character->plane.y = 0.0;
	}
	else
		set_east_west_orientation(character, orientation, plane_len);
}

void	character_initialize_position(t_character *character, t_world *world)
{
	int	i;
	int	j;

	if (!character || !world || !world->grid)
		return ;
	i = 0;
	while (i < world->height)
	{
		j = 0;
		while (j < world->width)
		{
			if (world->grid[i][j] == 'N' || world->grid[i][j] == 'S'
				|| world->grid[i][j] == 'E' || world->grid[i][j] == 'W')
			{
				character->pos.x = (double)j + 0.5;
				character->pos.y = (double)i + 0.5;
				character_set_orientation(character, world->grid[i][j]);
				world->grid[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

void	character_destroy(t_character *character)
{
	if (character)
		safe_free(character);
}
