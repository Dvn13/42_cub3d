/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 14:31:28 by gbodur            #+#    #+#             */
/*   Updated: 2025/12/23 14:31:29 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	main_loop_hook(t_engine *engine)
{
	if (engine && engine->is_running)
		engine_update(engine);
	return (0);
}

void	setup_event_hooks(t_engine *engine)
{
	if (!engine)
		return ;
	mlx_hook(engine->win_ptr, 2, 1L << 0, handle_key_press, engine);
	mlx_hook(engine->win_ptr, 3, 1L << 1, handle_key_release, engine);
	mlx_hook(engine->win_ptr, 17, 0, handle_window_close, engine);
	mlx_hook(engine->win_ptr, 6, 1L << 6, handle_mouse_movement, engine);
	mlx_hook(engine->win_ptr, 4, 1L << 2, handle_mouse_click, engine);
	mlx_loop_hook(engine->mlx_ptr, main_loop_hook, engine);
}
