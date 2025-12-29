/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:18:21 by gbodur            #+#    #+#             */
/*   Updated: 2025/12/23 19:18:22 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	return (renderer);
}

void	renderer_destroy(t_renderer *renderer, void *mlx_ptr)
{
	if (!renderer)
		return ;
	if (renderer->image_ptr)
		mlx_destroy_image(mlx_ptr, renderer->image_ptr);
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
