/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:19:06 by gbodur            #+#    #+#             */
/*   Updated: 2025/12/23 19:35:00 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	engine_main_loop(t_engine *engine)
{
	if (!engine)
		return (0);
	mlx_loop(engine->mlx_ptr);
	return (1);
}

void	engine_update(t_engine *engine)
{
	if (!engine || !engine->is_running)
		return ;
	process_input(engine);
	render_frame(engine);
}

void	engine_shutdown(t_engine *engine)
{
	if (!engine)
		return ;
	engine->is_running = 0;
	cleanup_engine(engine);
	exit(0);
}
