/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepere <jlepere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 10:57:32 by jlepere           #+#    #+#             */
/*   Updated: 2017/05/04 10:43:47 by jlepere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>

void	init_player(t_env *env)
{
	env->player.pos.x = -1;
	env->player.pos.y = -1;
	env->player.dir.x = -1;
	env->player.dir.y = 0;
	env->player.plane.x = 0;
	env->player.plane.y = 0.66;
	env->player.speed_rot = 0.06;
	env->player.speed_move = 0.05;
	env->player.move_up = 0;
	env->player.move_down = 0;
	env->player.move_left = 0;
	env->player.move_right = 0;
}

void	move_up(t_env *env)
{
	if (!env->map.data[(int)(env->player.pos.x + env->player.dir.x *
			env->player.speed_move) + (int)env->player.pos.y * env->map.width])
		env->player.pos.x += env->player.dir.x * env->player.speed_move;
	if (!env->map.data[(int)env->player.pos.x + (int)(env->player.pos.y +
			env->player.dir.y * env->player.speed_move) * env->map.width])
		env->player.pos.y += env->player.dir.y * env->player.speed_move;
}

void	move_down(t_env *env)
{
	if (!env->map.data[(int)(env->player.pos.x - env->player.dir.x *
			env->player.speed_move) + (int)env->player.pos.y * env->map.width])
		env->player.pos.x -= env->player.dir.x * env->player.speed_move;
	if (!env->map.data[(int)env->player.pos.x + (int)(env->player.pos.y -
			env->player.dir.y * env->player.speed_move) * env->map.width])
		env->player.pos.y -= env->player.dir.y * env->player.speed_move;
}

void	move_left(t_env *env)
{
	double	dir_x;
	double	plane_x;

	dir_x = env->player.dir.x;
	env->player.dir.x = dir_x * cos(env->player.speed_rot) -
		env->player.dir.y * sin(env->player.speed_rot);
	env->player.dir.y = dir_x * sin(env->player.speed_rot) +
		env->player.dir.y * cos(env->player.speed_rot);
	plane_x = env->player.plane.x;
	env->player.plane.x = plane_x * cos(env->player.speed_rot) -
		env->player.plane.y * sin(env->player.speed_rot);
	env->player.plane.y = plane_x * sin(env->player.speed_rot) +
		env->player.plane.y * cos(env->player.speed_rot);
}

void	move_right(t_env *env)
{
	double	dir_x;
	double	plane_x;

	dir_x = env->player.dir.x;
	env->player.dir.x = dir_x * cos(-env->player.speed_rot) -
		env->player.dir.y * sin(-env->player.speed_rot);
	env->player.dir.y = dir_x * sin(-env->player.speed_rot) +
		env->player.dir.y * cos(-env->player.speed_rot);
	plane_x = env->player.plane.x;
	env->player.plane.x = plane_x * cos(-env->player.speed_rot) -
		env->player.plane.y * sin(-env->player.speed_rot);
	env->player.plane.y = plane_x * sin(-env->player.speed_rot) +
		env->player.plane.y * cos(-env->player.speed_rot);
}
