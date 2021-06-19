/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 12:00:46 by labintei          #+#    #+#             */
/*   Updated: 2021/06/19 16:59:12 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# define KEY_A 97
# define KEY_W 119
# define KEY_D 100
# define KEY_S 115
# define KEY_RIGHT 65361
# define KEY_LEFT 65363
# define KEY_ESC 65307
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "mlx.h"
# include <math.h>

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixels;
	int		line_lenght;
	int		endian;
}				t_img;

typedef struct s_params
{
	void	*mlx;
	void	*mlx_win;
}				t_params;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bits_per_pixels;
	int		line_lenght;
	int		endian;
	int		width;
	int		height;
}				t_texture;

typedef struct s_player
{
	t_texture	p[12];
	int		x;
	int		y;
	int		pa;
	float	x_s;
	float	y_s;
	char	o;
	char	action;
}				t_player;

typedef struct s_sprite
{
	t_texture	p[4];
	int	size;
}			t_sprite;

typedef struct s_env
{
	t_params		p;
	t_player		play;
	t_sprite		c;
	t_texture		w;
	t_texture		f;
	t_texture		e;
	t_texture		i;
	int			fd;
	int			sizemapx;
	int			sizemapy;
	int			x;
	int			y;
	int			color;
	int			pas;
	int			delay;
	char		**map;
	char		key[5];
	int			frame;
	int			count;
}				t_env;

int	get_next_line(int fd, char **line);
void	f_load_texture(struct s_env *env);
int		clear_all(struct s_env *env);


#endif
