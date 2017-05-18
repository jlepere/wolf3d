/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepere <jlepere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 12:34:12 by jlepere           #+#    #+#             */
/*   Updated: 2017/05/04 10:39:43 by jlepere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "mlx.h"

static void	set_pixel(t_env *env, int x, int y, unsigned int c)
{
	int	i;

	i = (x * 4) + (y * env->mlx.s_line);
	env->mlx.pxl[i] = c;
	env->mlx.pxl[++i] = c >> 8;
	env->mlx.pxl[++i] = c >> 16;
}

static int	get_color(t_env *env)
{
	if (env->ray.hit_side == 1)
	{
		if ((env->ray.step.x == -1 && env->ray.step.y == -1) ||
			(env->ray.step.x == 1 && env->ray.step.y == -1))
			return (0xFF0000);
		if ((env->ray.step.x == -1 && env->ray.step.y == 1) ||
			(env->ray.step.x == 1 && env->ray.step.y == 1))
			return (0x00FF00);
	}
	if ((env->ray.step.x == -1 && env->ray.step.y == -1) ||
		(env->ray.step.x == -1 && env->ray.step.y == 1))
		return (0x0000FF);
	return (0xFF00FF);
}

void		draw_line(t_env *env, int x, int start, int end)
{
	int	y;
	int	color;

	y = -1;
	color = 0xFFFFFF;
	while (++y < start)
		set_pixel(env, x, y, color);
	color = get_color(env);
	set_pixel(env, x, y, 0x000000);
	while (++y < end && y < env->mlx.height)
		set_pixel(env, x, y, color);
	set_pixel(env, x, y, 0x000000);
	while (++y < env->mlx.height)
		set_pixel(env, x, y, 0x00FFFF);
}
