/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 14:31:24 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/01 13:21:26 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
