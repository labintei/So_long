/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 10:12:07 by labintei          #+#    #+#             */
/*   Updated: 2021/05/19 09:44:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H
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

typedef struct	s_list
{
	char	n;
	int		fd;
	char	*stock;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
	char	save;
	int		r[2];
	int		f[3];
	int		c[3];
	char	**map;
}				t_list;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixels;
	int		line_lenght;
	int		endian;
}				t_img;

typedef	struct	s_params
{
	void	*mlx;
	void	*mlx_win;
}				t_params;

typedef	struct	s_player
{
	double	x;
	double	y;
	double	pa;
}				t_player;

typedef	struct	s_texture
{
	void	*img;
	char	*addr;
	int		bits_per_pixels;
	int		line_lenght;
	int		endian;
	int		width;
	int		height;
}				t_texture;

typedef struct	s_env
{
	char		key[7];
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
	double		de;
	double		rot;
	double		*fov;
}				t_env;

char			checkbe_bis(struct s_list *l, struct s_params *i, int *r);
void			init_angle(struct s_env *env, int *i);
void			couleur_r(double *r, double *i, struct s_env *env, char *c);
void			init_p(struct s_env *env);
int				key_press(int keycode, struct s_env *env);
int				key_release(int	keycode, struct s_env *env);
int				t(struct s_env *env);
int				f_key(struct s_env *env);
int				ft_putstr_err(char *s);
void			stockdir(char **s1, char *s);
char			check_map(struct s_list *l);
int				print_background(struct s_env *env);
double			h(struct s_env *env, double x, double y);
void			drawcol_sprite(struct s_env *env, int *i, double d);
void			ajout_diff(struct s_env *env, double *i);
void			init_spe(struct s_env *env, double *i);
void			f_load_texture(struct	s_env *env);
void			ft_putstr(char *s);
int				treat_map(struct s_list *l);
char			ft_find(char c, char *s);
void			ft_dir(struct s_list *l, char *s, int *i);
void			ft_number(struct s_list *l, char *s, int *i);
void			map(struct s_list *l);
void			ft_map_cut(struct s_list *l, int j);
void			ft_put_map(struct s_list *l, int *y, int j);
char			checkbe(struct s_list *l, struct s_params *i);
char			checkimg(char *s, struct s_params *i);
void			drawray(struct s_env *env);
void			ft_map_cut_2(struct s_list *l, int *y, int j);
void			draw_minimap(struct s_env *env);
void			ft_dir_bis(struct s_list *l, char *c, char *t);
void			stock_number(char *s, int *i, int *val, char c);
int				treat_map_1(struct s_list *l, int *i, int *j);
int				open_window(struct s_env	*env);
int				create_trtgb(int t, int r, int g, int b);
void			my_put_pixel(struct s_img *i, int x, int y, int color);
void			drawcarre(int x, int y, int largeur, struct s_env *env);
void			maxxy(struct s_env *env);
void			dray(struct s_env *env, double a);
void			drawfov(struct s_env *env);
void			f_compare(struct s_env *env, double *i, char *s, double a);
void			drawcol1(struct s_env *env, double *r);
void			drawfov(struct s_env *env);
void			drawcols(struct s_env *env, int *i, double y);
int				index_color(int x, int y, struct s_texture *text);
void			draw_sprite(struct	s_env *env);
void			dray_bis(struct s_env *env, double a);
void			dvarconst(struct s_env *env);
void			dvar(struct s_env *env, double a);
void			dray_angle_sprite(struct s_env *env, double d);
void			init_envi(struct s_env *env, double a);
void			init_i(struct s_env *env, double *i);
void			drawdir_bis_6(struct s_env *env, double x, double y);
void			drawdir_bis_7(struct s_env *env, double x, double y);
void			stock_drawfov(struct	s_env *env);
void			drawfov_bis(struct	s_env *env);
int				bmp_save_file(struct s_env *env);
int				destroy_ta_vie(struct s_env *env);

int				ft_strlen(char *s);;
char			*ft_join(char *s1, char *s2, int v);
void			test(int fd, char **s, char **n);


#endif
