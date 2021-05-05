/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 10:12:07 by labintei          #+#    #+#             */
/*   Updated: 2021/05/05 14:00:46 by user42           ###   ########.fr       */
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
	int			c;
	int			pas;
	int			xmax;
	int			ymax;
	int			nbray;
	t_list		l;
	char		save;
	t_params	p;
	t_img		i;
	t_player	play;
	t_texture	t[5];
	double		diff[4];
	double		var[5];
	double		envi[4];
	double		sp[5];
	double		rot;
	double		fov[20000];
}					t_env;

int			ft_putstr_err(char *s);
void		stockdir(struct s_list *l,char **s1, char *s);
char		check_map(struct s_list *l);
void		print_background(struct s_env *env);
double		cald(struct s_env *env, double x, double y);
void		drawcol_sprite(struct s_env *env, int *i, double d);
void		ajout_diff(struct s_env *env, double *i);
void		init_spe(struct s_env *env, int keycode,double *i);
void		f_load_texture(struct	s_env *env);
void		ft_putstr(char *s);
void		treat_map(struct s_list *l);
char		ft_find(char c, char *s);
void		ft_dir(struct s_list *l, char *s, int *i);
void		ft_number(struct s_list *l, char *s, int *i);
void		map(struct s_list *l);
void		ft_map_cut(struct s_list *l, int j);
void		ft_put_map(struct s_list *l, int *y, int j);
char		checkbe(struct s_list *l, struct s_params *i);
char		checkimg(char *s, struct s_params *i);
void		drawray(struct s_env *env);

int			open_window(struct s_env	*env);

int		create_trtgb(int t, int r, int g, int b);
void	my_put_pixel(struct s_img *i, int x, int y, int color);
void	drawcarre(int x, int y, int largeur, struct s_env *env);
void	maxxy(struct s_env *env);
void	dray(struct s_env *env,double a);
void	drawfov(struct s_env *env);

void	f_compare(struct s_env *env, double *i, double a);
void	drawcol1(struct s_env *env, double *r);
void	drawcol2(struct s_env *env,int *a, int color,double x, double y);
void	drawfov(struct s_env *env);
void	drawcoln(struct s_env *env, int *i,double y);
void	drawcols(struct s_env *env, int *i,double y);
void	drawcolw(struct s_env *env, int *i, double x);
void	drawcole(struct s_env *env, int *i, double x);


int		index_color(int x, int y, struct s_texture *text);

void	draw_sprite(struct	s_env *env);


void	dray_bis(struct s_env *env, double a);
int		f_compare_bis(struct s_env *env, double x1, double y1, double x, double y, double a);

void	dvarconst(struct s_env *env);
void	dvar(struct s_env *env, double a);

void	dray_angle_sprite(struct s_env *env, double d);
void	init_envi(struct s_env *env, double a);
void	init_i(struct s_env *env, double *i);


void	drawdir_bis_6(struct s_env *env, double x,double y);
void	drawdir_bis_7(struct s_env *env, double x,double y);


void	stock_drawfov(struct	s_env *env);
void	drawfov_bis(struct	s_env *env);


int		bmp_save_file(struct s_env *env);

void	destroy_ta_vie(struct s_env *env);

#endif
