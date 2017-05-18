/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepere <jlepere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:28:16 by jlepere           #+#    #+#             */
/*   Updated: 2017/05/11 13:53:31 by jlepere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"
#include "mlx.h"

void	my_exit(char *str, t_env *env)
{
	free_env(env);
	ft_exit(str, -1);
}

int		main(int argc, char **argv)
{
	t_env	*env;

	env = NULL;
	if (argc != 2)
		my_exit("Nombre d'argument invalide !", env);
	if (!(env = init_env("Wolf3D", 512, 484)))
		my_exit("Impossible d'initialiser l'environement !", env);
	if (!init_map(env, argv[1]))
		my_exit("Impossible de charger la map !", env);
	mlx_do_key_autorepeatoff(env->mlx.ptr);
	mlx_hook(env->mlx.win, 2, 1, keys_events, env);
	mlx_hook(env->mlx.win, 3, 2, keys_events, env);
	mlx_hook(env->mlx.win, KEYPRESS, KEYPRESS_MASK, win_close_event, env);
	mlx_loop_hook(env->mlx.ptr, run_loop, env);
	mlx_loop(env->mlx.ptr);
	free_env(env);
	return (0);
}
