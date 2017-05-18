/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepere <jlepere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:46:50 by jlepere           #+#    #+#             */
/*   Updated: 2017/05/11 13:54:47 by jlepere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"
#include "mlx.h"
#include <stdlib.h>

int	win_close_event(t_env *env)
{
	mlx_destroy_image(env->mlx.ptr, env->mlx.img);
	mlx_destroy_window(env->mlx.ptr, env->mlx.win);
	free_env(env);
	exit(0);
}

int	keys_events(int keycode, t_env *env)
{
	if (keycode == KEY_ESC)
		win_close_event(env);
	if (keycode == KEY_UP)
		env->player.move_up = !env->player.move_up;
	else if (keycode == KEY_DOWN)
		env->player.move_down = !env->player.move_down;
	if (keycode == KEY_LEFT)
		env->player.move_left = !env->player.move_left;
	else if (keycode == KEY_RIGHT)
		env->player.move_right = !env->player.move_right;
	return (0);
}
