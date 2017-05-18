/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepere <jlepere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:32:42 by jlepere           #+#    #+#             */
/*   Updated: 2017/05/11 13:50:25 by jlepere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# define KEY_ESC 53
# define KEY_UP 13
# define KEY_LEFT 0
# define KEY_RIGHT 2
# define KEY_DOWN 1
# define KEYPRESS 17
# define KEYPRESS_MASK (1L << 17)
# include <time.h>

typedef struct		s_vec2i
{
	int				x;
	int				y;
}					t_vec2i;

typedef struct		s_vec2d
{
	double			x;
	double			y;
}					t_vec2d;

typedef struct		s_mlx
{
	void			*ptr;
	void			*win;
	void			*img;
	char			*pxl;
	int				width;
	int				height;
	int				s_line;
	char			init;
}					t_mlx;

typedef struct		s_map
{
	int				width;
	int				height;
	int				*data;
}					t_map;

typedef struct		s_ray
{
	struct s_vec2d	pos;
	struct s_vec2i	map;
	struct s_vec2d	dir;
	struct s_vec2i	step;
	struct s_vec2d	wall;
	struct s_vec2d	delta;
	float			dist;
	int				hit;
	int				hit_side;
}					t_ray;

typedef struct		s_player
{
	struct s_vec2d	pos;
	struct s_vec2d	dir;
	struct s_vec2d	plane;
	double			cam;
	double			speed_rot;
	double			speed_move;
	char			move_up;
	char			move_left;
	char			move_right;
	char			move_down;
}					t_player;

typedef struct		s_env
{
	struct s_mlx	mlx;
	struct s_map	map;
	struct s_ray	ray;
	struct s_player	player;
	clock_t			current_frame;
	clock_t			next_frame;
}					t_env;

void				my_exit(char *str, t_env *env);

t_env				*init_env(char *title, int width, int height);
void				*free_env(t_env *env);
int					run_loop(t_env *env);

int					init_map(t_env *env, char *file);

void				init_player(t_env *env);
void				move_up(t_env *env);
void				move_down(t_env *env);
void				move_left(t_env *env);
void				move_right(t_env *env);

int					win_close_event(t_env *env);
int					keys_events(int keycode, t_env *env);

void				raycasting(t_env *env);

void				draw_line(t_env *env, int x, int start, int end);

#endif
