/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 14:31:24 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/05 20:17:02 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	interact_with_door(t_engine *engine)
{
	int		target_x;
	int		target_y;
	char	cell;
	double	dx;
	double	dy;

	target_x = (int)(engine->character->pos.x + engine->character->dir.x * 1.0);
	target_y = (int)(engine->character->pos.y + engine->character->dir.y * 1.0);
	if (target_x < 0 || target_x >= engine->world->width || target_y < 0
		|| target_y >= engine->world->height)
		return ;
	cell = world_get_cell(engine->world, target_x, target_y);
	if (cell == 'D')
		engine->world->grid[target_y][target_x] = 'O';
	else if (cell == 'O')
	{
		dx = engine->character->pos.x - (target_x + 0.5);
		dy = engine->character->pos.y - (target_y + 0.5);
		if (dx * dx + dy * dy < 0.64)
			return ;
		engine->world->grid[target_y][target_x] = 'D';
	}
}

int	handle_key_press(int keycode, t_engine *engine)
{
	if (!engine || !engine->character)
		return (0);
	if (keycode == KEY_ESC)
		engine_shutdown(engine);
	else if (keycode == KEY_W)
		engine->key_w = 1;
	else if (keycode == KEY_A)
		engine->key_a = 1;
	else if (keycode == KEY_S)
		engine->key_s = 1;
	else if (keycode == KEY_D)
		engine->key_d = 1;
	else if (keycode == KEY_E)
		interact_with_door(engine);
	else if (keycode == KEY_M)
		mouse_toggle(engine);
	else if (keycode == KEY_LEFT)
		engine->key_left = 1;
	else if (keycode == KEY_RIGHT)
		engine->key_right = 1;
	return (0);
}

int	handle_key_release(int keycode, t_engine *engine)
{
	if (!engine)
		return (0);
	if (keycode == KEY_W)
		engine->key_w = 0;
	else if (keycode == KEY_A)
		engine->key_a = 0;
	else if (keycode == KEY_S)
		engine->key_s = 0;
	else if (keycode == KEY_D)
		engine->key_d = 0;
	else if (keycode == KEY_LEFT)
		engine->key_left = 0;
	else if (keycode == KEY_RIGHT)
		engine->key_right = 0;
	return (0);
}

int	handle_window_close(t_engine *engine)
{
	if (engine)
		engine_shutdown(engine);
	return (0);
}
