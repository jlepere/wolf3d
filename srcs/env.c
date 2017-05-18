/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepere <jlepere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:40:47 by jlepere           #+#    #+#             */
/*   Updated: 2017/05/11 13:56:42 by jlepere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"
#include "mlx.h"

static void	init_img(t_env *env)
{
	int	bpp;
	int	end;

	bpp = 0;
	end = 0;
	env->mlx.s_line = 0;
	env->mlx.img = mlx_new_image(env->mlx.ptr, env->mlx.width, env->mlx.height);
	env->mlx.pxl = mlx_get_data_addr(env->mlx.img, &(bpp), &(env->mlx.s_line),
		&(end));
}

t_env		*init_env(char *title, int width, int height)
{
	t_env	*env;

	if (!(env = ft_memalloc(sizeof(struct s_env))))
		return (NULL);
	if (!(env->mlx.ptr = mlx_init()) ||
		!(env->mlx.win = mlx_new_window(env->mlx.ptr, width, height, title)))
		return (free_env(env));
	env->mlx.width = width;
	env->mlx.height = height;
	env->mlx.init = 0;
	env->map.width = -1;
	env->map.height = -1;
	env->ray.pos.x = -1;
	env->ray.pos.y = -1;
	init_img(env);
	init_player(env);
	return (env);
}

void		*free_env(t_env *env)
{
	if (!env)
		return (NULL);
	if (env->map.data)
		ft_memdel((void**)&env->map.data);
	ft_memdel((void**)&env);
	return ((env = NULL));
}

int			run_loop(t_env *env)
{
	env->current_frame = clock();
	if (env->next_frame > env->current_frame)
		return (0);
	env->next_frame = env->current_frame + (CLOCKS_PER_SEC / 100);
	if (env->player.move_up)
		move_up(env);
	else if (env->player.move_down)
		move_down(env);
	if (env->player.move_left)
		move_left(env);
	else if (env->player.move_right)
		move_right(env);
	if (env->mlx.init && !env->player.move_up && !env->player.move_down &&
			!env->player.move_left && !env->player.move_right && env)
		return (0);
	env->mlx.init = 1;
	raycasting(env);
	mlx_clear_window(env->mlx.ptr, env->mlx.win);
	mlx_put_image_to_window(env->mlx.ptr, env->mlx.win, env->mlx.img, 0, 0);
	return (0);
}
