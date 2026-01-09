/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_load_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:46:54 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/09 18:45:49 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	load_sprites_first(t_engine *engine)
{
	engine->renderer->sprite_textures[0] = texture_allocate();
	if (!texture_load_from_file(engine->renderer->sprite_textures[0],
			engine->mlx_ptr, "assets/sprites/Gold_21.xpm"))
		return (0);
	engine->renderer->sprite_textures[1] = texture_allocate();
	if (!texture_load_from_file(engine->renderer->sprite_textures[1],
			engine->mlx_ptr, "assets/sprites/Gold_22.xpm"))
		return (0);
	engine->renderer->sprite_textures[2] = texture_allocate();
	if (!texture_load_from_file(engine->renderer->sprite_textures[2],
			engine->mlx_ptr, "assets/sprites/Gold_23.xpm"))
		return (0);
	engine->renderer->sprite_textures[3] = texture_allocate();
	if (!texture_load_from_file(engine->renderer->sprite_textures[3],
			engine->mlx_ptr, "assets/sprites/Gold_24.xpm"))
		return (0);
	engine->renderer->sprite_textures[4] = texture_allocate();
	if (!texture_load_from_file(engine->renderer->sprite_textures[4],
			engine->mlx_ptr, "assets/sprites/Gold_25.xpm"))
		return (0);
	return (1);
}

int	load_sprites_second(t_engine *engine)
{
	engine->renderer->sprite_textures[5] = texture_allocate();
	if (!texture_load_from_file(engine->renderer->sprite_textures[5],
			engine->mlx_ptr, "assets/sprites/Gold_26.xpm"))
		return (0);
	engine->renderer->sprite_textures[6] = texture_allocate();
	if (!texture_load_from_file(engine->renderer->sprite_textures[6],
			engine->mlx_ptr, "assets/sprites/Gold_27.xpm"))
		return (0);
	engine->renderer->sprite_textures[7] = texture_allocate();
	if (!texture_load_from_file(engine->renderer->sprite_textures[7],
			engine->mlx_ptr, "assets/sprites/Gold_28.xpm"))
		return (0);
	engine->renderer->sprite_textures[8] = texture_allocate();
	if (!texture_load_from_file(engine->renderer->sprite_textures[8],
			engine->mlx_ptr, "assets/sprites/Gold_29.xpm"))
		return (0);
	engine->renderer->sprite_textures[9] = texture_allocate();
	if (!texture_load_from_file(engine->renderer->sprite_textures[9],
			engine->mlx_ptr, "assets/sprites/Gold_30.xpm"))
		return (0);
	return (1);
}
