/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepere <jlepere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 09:22:46 by jlepere           #+#    #+#             */
/*   Updated: 2017/05/04 13:37:19 by jlepere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>

static void	draw_raycasting(t_env *env, int x)
{
	int	end;
	int	start;
	int	height;

	height = (int)(env->mlx.height / env->ray.dist);
	start = -height / 2 + env->mlx.height / 2;
	if (start < 0)
		start = 0;
	end = height / 2 + env->mlx.height / 2;
	if (end >= env->mlx.height)
		end = env->mlx.height - 1;
	draw_line(env, x, start, end);
}

static void	dist_raycasting(t_env *env)
{
	while (!env->ray.hit)
	{
		if (env->ray.wall.x < env->ray.wall.y)
		{
			env->ray.wall.x += env->ray.delta.x;
			env->ray.map.x += env->ray.step.x;
			env->ray.hit_side = 0;
		}
		else
		{
			env->ray.wall.y += env->ray.delta.y;
			env->ray.map.y += env->ray.step.y;
			env->ray.hit_side = 1;
		}
		if (env->map.data[env->ray.map.x + env->ray.map.y * env->map.width] > 0)
		{
			env->ray.hit = 1;
			if (!env->ray.hit_side)
				env->ray.dist = (env->ray.map.x - env->ray.pos.x +
						(1 - env->ray.step.x) / 2) / env->ray.dir.x;
			else
				env->ray.dist = (env->ray.map.y - env->ray.pos.y +
						(1 - env->ray.step.y) / 2) / env->ray.dir.y;
		}
	}
}

static void	wall_raycasting(t_env *env)
{
	if (env->ray.dir.x < 0)
	{
		env->ray.step.x = -1;
		env->ray.wall.x = (env->ray.pos.x - env->ray.map.x)
			* env->ray.delta.x;
	}
	else
	{
		env->ray.step.x = 1;
		env->ray.wall.x = (env->ray.map.x + 1 - env->ray.pos.x)
			* env->ray.delta.x;
	}
	if (env->ray.dir.y < 0)
	{
		env->ray.step.y = -1;
		env->ray.wall.y = (env->ray.pos.y - env->ray.map.y)
			* env->ray.delta.y;
	}
	else
	{
		env->ray.step.y = 1;
		env->ray.wall.y = (env->ray.map.y + 1 - env->ray.pos.y)
			* env->ray.delta.y;
	}
}

static void	init_raycasting(t_env *env, int x)
{
	env->player.cam = 2 * x / (double)env->mlx.width - 1;
	env->ray.map.x = (int)env->ray.pos.x;
	env->ray.map.y = (int)env->ray.pos.y;
	env->ray.dir.x = env->player.dir.x + env->player.plane.x * env->player.cam;
	env->ray.dir.y = env->player.dir.y + env->player.plane.y * env->player.cam;
	env->ray.delta.x = sqrt(1 + (env->ray.dir.y * env->ray.dir.y) /
		(env->ray.dir.x * env->ray.dir.x));
	env->ray.delta.y = sqrt(1 + (env->ray.dir.x * env->ray.dir.x) /
		(env->ray.dir.y * env->ray.dir.y));
	env->ray.hit = 0;
	env->ray.dist = -1;
	env->ray.hit_side = -1;
}

void		raycasting(t_env *env)
{
	int	x;

	x = 0;
	env->ray.pos.x = env->player.pos.x;
	env->ray.pos.y = env->player.pos.y;
	while (x < env->mlx.width)
	{
		init_raycasting(env, x);
		wall_raycasting(env);
		dist_raycasting(env);
		draw_raycasting(env, x);
		x++;
	}
}
