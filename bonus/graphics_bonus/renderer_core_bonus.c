/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_core_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdivan <mdivan@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:18:21 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/03 04:01:36 by mdivan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	init_renderer_buffers(t_renderer *renderer, void *mlx_ptr)
{
	renderer->z_buffer = safe_calloc(SCREEN_WIDTH, sizeof(double));
	if (!renderer->z_buffer)
	{
		renderer_destroy(renderer, mlx_ptr);
		return (0);
	}
	renderer->sprite_textures = safe_calloc(10, sizeof(t_texture *));
	if (!renderer->sprite_textures)
	{
		renderer_destroy(renderer, mlx_ptr);
		return (0);
	}
	renderer->sprite_text_count = 10;
	return (1);
}

t_renderer	*renderer_create(void *mlx_ptr)
{
	t_renderer	*renderer;

	renderer = safe_calloc(1, sizeof(t_renderer));
	if (!renderer)
		return (NULL);
	renderer->image_ptr = mlx_new_image(mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!renderer->image_ptr)
	{
		safe_free(renderer);
		return (NULL);
	}
	renderer->image_data = mlx_get_data_addr(renderer->image_ptr,
			&renderer->bits_per_pixel, &renderer->size_line, &renderer->endian);
	renderer->image_width = SCREEN_WIDTH;
	renderer->image_height = SCREEN_HEIGHT;
	if (!init_renderer_buffers(renderer, mlx_ptr))
		return (NULL);
	return (renderer);
}

void	renderer_destroy(t_renderer *renderer, void *mlx_ptr)
{
	int	i;

	if (!renderer)
		return ;
	if (renderer->image_ptr)
		mlx_destroy_image(mlx_ptr, renderer->image_ptr);
	if (renderer->z_buffer)
		safe_free(renderer->z_buffer);
	if (renderer->sprite_textures)
	{
		i = 0;
		while (i < renderer->sprite_text_count)
		{
			if (renderer->sprite_textures[i])
				texture_destroy(renderer->sprite_textures[i], mlx_ptr);
			i++;
		}
		safe_free(renderer->sprite_textures);
	}
	destroy_bonus_textures(renderer, mlx_ptr);
	safe_free(renderer);
}

void	renderer_clear_screen(t_renderer *renderer, int color)
{
	int	x;
	int	y;

	if (!renderer || !renderer->image_data)
		return ;
	y = 0;
	while (y < renderer->image_height)
	{
		x = 0;
		while (x < renderer->image_width)
		{
			renderer_put_pixel(renderer, x, y, color);
			x++;
		}
		y++;
	}
}

void	renderer_draw_to_window(t_renderer *renderer, void *mlx_ptr,
		void *win_ptr)
{
	if (!renderer || !renderer->image_ptr)
		return ;
	mlx_put_image_to_window(mlx_ptr, win_ptr, renderer->image_ptr, 0, 0);
}
