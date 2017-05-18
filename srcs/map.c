/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepere <jlepere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:54:41 by jlepere           #+#    #+#             */
/*   Updated: 2017/05/04 14:23:14 by jlepere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"

static int	read_map_info(t_env *env, t_file *map)
{
	char	*line;
	char	**data;

	if (ft_next_line(map, &line) < 1)
		return (0);
	if ((data = ft_strsplit(line, ' ')) && ft_arrlen(data) == 4)
	{
		env->map.width = ft_atoi(data[0]) + 2;
		env->map.height = ft_atoi(data[1]) + 2;
		env->player.pos.x = ft_atoi(data[2]) + 1;
		env->player.pos.y = ft_atoi(data[3]) + 1;
	}
	ft_strdel(&line);
	ft_arrdel(data);
	if (env->map.width - 2 <= 2 || env->map.height - 2 <= 2
		|| env->player.pos.x < 0 || env->player.pos.y < 0 ||
		!(env->map.data = ft_memalloc(sizeof(int) *
		(env->map.width * env->map.height))))
		return (0);
	return (1);
}

static void	init_map_data(t_env *env)
{
	int	x;
	int	y;

	y = -1;
	while (++y < env->map.height)
	{
		x = -1;
		while (++x < env->map.width)
		{
			if (y == 0 || y == env->map.height - 1 ||
				x == 0 || x == env->map.width - 1)
				env->map.data[x + y * env->map.width] = 1;
		}
	}
}

static int	read_map_data(t_env *env, t_file *map)
{
	char	*line;
	char	**tmp;
	t_vec2i	pos;

	pos.y = 0;
	init_map_data(env);
	while (ft_next_line(map, &line) && ++pos.y != 0)
	{
		pos.x = 0;
		if (!(tmp = ft_strsplit(line, ' ')) ||
			(int)ft_arrlen(tmp) != env->map.width - 2)
			pos.y = -1;
		while (tmp[++pos.x - 1] && pos.y != -1)
			env->map.data[pos.x + pos.y *
			env->map.width] = ft_atoi(tmp[pos.x - 1]);
		ft_arrdel(tmp);
		ft_strdel(&line);
	}
	if (pos.y == -1 || (pos.x + 1) * (pos.y + 2) != env->map.width *
		env->map.height)
		return (0);
	return (1);
}

static void	check_player_pos(t_env *env)
{
	if (env->player.pos.x >= env->map.width ||
		env->player.pos.y >= env->map.height ||
		env->map.data[(int)env->player.pos.x + (int)env->player.pos.y *
		env->map.width])
		ft_exit("Le joueur ne peut pas spawn dans un mur !", -1);
	env->player.pos.x += 0.5f;
	env->player.pos.y += 0.5f;
}

int			init_map(t_env *env, char *file)
{
	t_file	*map;
	int		err;

	err = 1;
	if (!(map = ft_open_file(file)))
		return (0);
	if (!(read_map_info(env, map)) || !(read_map_data(env, map)))
		err = 0;
	check_player_pos(env);
	ft_free_file(map);
	return (err);
}
