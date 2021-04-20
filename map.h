/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 10:12:07 by labintei          #+#    #+#             */
/*   Updated: 2021/04/07 14:27:11 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include "mlx.h"
#include <math.h>

typedef struct		s_list
{
	char	n;
	int		fd;
	char	*stock;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
	int		r[2];
	int		f[3];
	int		c[3];
	char	**map;
}					t_list;


typedef struct		s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixels;
	int		line_lenght;
	int		endian;
}					t_img;

typedef	struct		s_params
{
	void	*mlx;
	void	*mlx_win;
}					t_params;

typedef	struct		s_player
{
	double	x;
	double	y;
	double	pa;
}					t_player;

typedef	struct		s_texture
{
	void	*img;
	char	*addr;
	int		bits_per_pixels;
	int		line_lenght;
	int		endian;
	int		width;
	int		height;
}					t_texture;

typedef struct		s_env
{
	int			pas;
	int			xmax;
	int			ymax;
	int			nbray;
	t_list		l;
	t_params	p;
	t_img		i;
	t_player	play;
	t_texture	t[5];
	double		mur[2];
	double		diff[4];
	double		var[5];
	double		envi[4];
	double		lim[2];
	double		tang;
	/* 0 NORD 1 SUD 2 WEST 3 EAST 4 SPRITE*/
}					t_env;

void		f_load_texture(struct	s_env *env);

void		ft_putstr(char *s);
void		treat_map(struct s_list *l);
char		ft_find(char c, char *s);
void		ft_dir(struct s_list *l, char *s, int *i);
void		ft_number(struct s_list *l, char *s, int *i);
void		map(struct s_list *l);
void		ft_map_cut(struct s_list *l, int j);
void		ft_put_map(struct s_list *l, int min, int max, int j, int ligne);
char		checkbe(struct s_list *l, struct s_params *i);
char		checkimg(char *s, struct s_params *i);
void		drawray(struct s_env *env);

void		open_windows2(struct s_env	*env);

int		create_trtgb(int t, int r, int g, int b);
void	my_put_pixel(struct s_img *i, int x, int y, int color);
void	drawcarre(int x, int y, int largeur, struct s_env *env, int color);
void	maxxy(struct s_env *env, int *xmax,int *ymax);
void	dray(struct s_env *env,double a);
void	drawfov(struct s_env *env);

double	cald(double x1, double x2,double y1, double y2);
void	f_compare(struct s_env *env, double x1, double y1, double x, double y, double a);
void	drawcol1(struct s_env *env,double *d, double a, int color, double x, double y);
void	drawcol2(struct s_env *env,int *a, int color,double x, double y);
void	drawfov(struct s_env *env);
void	drawcolN(struct s_env *env, int *i,double y);
void	drawcolS(struct s_env *env, int *i,double y);
void	drawcolW(struct s_env *env, int *i, double x);
void	drawcolE(struct s_env *env, int *i, double x);


int		index_color(int x, int y, struct s_texture *text);

void	draw_sprite(struct	s_env *env);


void	dray_bis(struct s_env *env, double a);
int		f_compare_bis(struct s_env *env, double x1, double y1, double x, double y, double a);

void	dvarconst(struct s_env *env);
void	dvar(struct s_env *env, double a);

void	dray_angle_sprite(struct s_env *env, double a, double d);
void	init_envi(struct s_env *env, double a);
void	init_i(struct s_env *env, double *i);


void	drawdir_bis_6(struct s_env *env, double x,double y);
void	drawdir_bis_7(struct s_env *env, double x,double y);

#endif
