/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdivan <mdivan@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:18:25 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/03 04:01:32 by mdivan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	renderer_put_pixel(t_renderer *renderer, int x, int y, int color)
{
	char	*pixel;

	if (!renderer || !renderer->image_data || x < 0 || y < 0
		|| x >= renderer->image_width || y >= renderer->image_height)
		return ;
	pixel = renderer->image_data + (y * renderer->size_line + x
			* (renderer->bits_per_pixel / 8));
	*(int *)pixel = color;
}

int	renderer_get_pixel_color(t_texture *texture, int x, int y)
{
	char	*pixel;

	if (!texture || !texture->data || x < 0 || y < 0 || x >= texture->width
		|| y >= texture->height)
		return (0);
	pixel = texture->data + (y * texture->size_line + x
			* (texture->bits_per_pixel / 8));
	return (*(int *)pixel);
}

void	render_frame(t_engine *engine)
{
	if (!engine || !engine->renderer || !engine->character || !engine->world)
		return ;
	renderer_clear_screen(engine->renderer, COLOR_BLACK);
	render_floor_ceiling(engine);
	render_walls(engine);
	render_sprites(engine);
	render_minimap(engine);
	renderer_draw_to_window(engine->renderer, engine->mlx_ptr, engine->win_ptr);
}
