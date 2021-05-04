/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawray5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 10:50:11 by labintei          #+#    #+#             */
/*   Updated: 2021/04/30 14:27:30 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int			index_color(int x, int y, struct s_texture *text)
{
	int		index;

	index = (y * text->line_lenght + x * (text->bits_per_pixels / 8));
	return (((int *)text->addr)[index / 4]);
}

void		f_load_texture(struct s_env *env)
{
	env->t[0].img = mlx_xpm_file_to_image(env->p.mlx, env->l.no, \
	&(env->t[0].width), &(env->t[0].height));
	env->t[0].addr = mlx_get_data_addr(env->t[0].img, &(env->t[0].\
	bits_per_pixels), &(env->t[0].line_lenght), &(env->t[0].endian));
	env->t[1].img = mlx_xpm_file_to_image(env->p.mlx, env->l.so, \
	&(env->t[1].width), &(env->t[1].height));
	env->t[1].addr = mlx_get_data_addr(env->t[1].img, &(env->t[1].\
	bits_per_pixels), &(env->t[1].line_lenght), &(env->t[1].endian));
	env->t[2].img = mlx_xpm_file_to_image(env->p.mlx, env->l.we, \
	&(env->t[2].width), &(env->t[2].height));
	env->t[2].addr = mlx_get_data_addr(env->t[2].img, &(env->t[2].\
	bits_per_pixels), &(env->t[2].line_lenght), &(env->t[2].endian));
	env->t[3].img = mlx_xpm_file_to_image(env->p.mlx, env->l.ea, \
	&(env->t[3].width), &(env->t[3].height));
	env->t[3].addr = mlx_get_data_addr(env->t[3].img, &(env->t[3].\
	bits_per_pixels), &(env->t[3].line_lenght), &(env->t[3].endian));
	env->t[4].img = mlx_xpm_file_to_image(env->p.mlx, env->l.s, \
	&(env->t[4].width), &(env->t[4].height));
	env->t[4].addr = mlx_get_data_addr(env->t[4].img, &(env->t[4].\
	bits_per_pixels), &(env->t[4].line_lenght), &(env->t[4].endian));
	return ;
}

void		f_compare(struct s_env *env, double x1, double y1, double x, double y, double a)
{
	double		fin;
	double		o;
	int			color;

	if (cald_bis(env, x1, y1) < cald_bis(env, x, y) || a == 0 || a == M_PI)
	{
		color = (x1 > env->play.x) ? 1 : 2;
		fin = (cald_bis(env, x1, y1));
		o = fin;
		drawcol1(env, &fin, a, color, x1, y1);
		return (dray_angle_sprite(env, a, o));
	}
	if (cald_bis(env, x1, y1) >= cald_bis(env, x, y) || a == env->var[3] || a == env->var[4])
	{
		color = (y > env->play.y) ? 3 : 4;
		fin = (cald_bis(env, x, y));
		o = fin;
		drawcol1(env, &fin, a, color, x, y);
		return (dray_angle_sprite(env, a, o));
	}
	return ;
}

void		drawcol1(struct s_env *env, double *d, double a, int color, double x, double y)
{
	double	hmur;
	int		i[2];
	double	dist;

	dist = *d * cos((a > env->play.pa) ? a - env->play.pa : env->play.pa - a);
	hmur = (int)(env->l.r[1] / (dist));
	i[0] = (env->l.r[1] / 2) - (hmur / 2);
	i[1] = (env->l.r[1] / 2) + (hmur / 2);
	if (color == 1)
		drawcoln(env, i, y);
	if (color == 2)
		drawcols(env, i, y);
	if (color == 3)
		drawcole(env, i, x);
	if (color == 4 || color == 0)
		drawcolw(env, i, x);
	return ;
}

void		dvarconst(struct s_env *env)
{
	env->var[0] = (((M_PI / 2)) / env->l.r[0]);
	env->var[1] = (env->l.r[0] / 2) * env->var[0];
	env->var[2] = 2 * M_PI;
	env->var[3] = 3 * (M_PI / 2);
	env->var[4] = M_PI / 2;
	env->rot = (2 * M_PI) / 360;
	return ;
}

void		stock_drawfov(struct s_env *env)
{
	double	dist;
	double	test;
	int		n;
	double	l[4000];

	test = M_PI / 4;
	l[0] = 0;
	n = 0;
	dist = env->l.r[0] / (2 * tan(M_PI / 4));
	while (n <= (env->l.r[0] / 2))
	{
		n++;
		l[n] = test - fabs((atan(abs(((int)env->l.r[0] / 2) - n) / dist)));
		test -= fabs(l[n]);
	}
	test = 0;
	while (n <= env->l.r[0])
	{
		n++;
		l[n] = fabs((atan((n - env->l.r[0] / 2) / dist))) - test;
		test += fabs(l[n]);
	}
	n = -1;
	while (++n <= ((int)(env->l.r[0] / 2)))
		env->fov[n] = l[n];
	return ;
}

void		drawfov_bis(struct s_env *env)
{
	double	angle;
	int		n;

	env->play.pa += (env->play.pa < 0) ? 2 * M_PI : 0;
	env->play.pa -= (env->play.pa > 2 * M_PI) ? 2 * M_PI : 0;
	env->nbray = 0;
	angle = env->play.pa - M_PI / 4;
	while (env->nbray <= env->l.r[0] / 2)
	{
		dray(env, angle);
		env->nbray++;
		angle += fabs(env->fov[env->nbray]);
	}
	n = env->nbray;
	while (env->nbray < (env->l.r[0]))
	{
		dray(env, angle);
		env->nbray++;
		angle += fabs(env->fov[--n]);
	}
	return ;
}

void		drawcoln(struct s_env *env, int *i, double y)
{
	int		start;
	int		color;
	double	c[3];

	c[1] = ((float)env->t[0].height) / ((float)(i[1] - i[0]));
	start = i[0];
	i[0] = (i[0] < 0) ? 0 : i[0];
	c[0] = ((float)(y - ((int)y))) * ((float)env->t[0].width);
	while (i[0] >= 0 && i[0] < env->l.r[1] && i[0] <= i[1])
	{
		c[2] = (i[0] - start) * c[1];
		color = index_color(c[0], c[2], &(env->t[0]));
		my_put_pixel(&(env->i), env->nbray, i[0], color);
		i[0]++;
	}
	return ;
}

void		drawcols(struct s_env *env, int *i, double y)
{
	int		start;
	int		color;
	double	c[3];

	c[1] = ((float)env->t[1].height) / ((float)(i[1] - i[0]));
	start = i[0];
	i[0] = (i[0] < 0) ? 0 : i[0];
	c[0] = ((float)(y - ((int)y)) * (float)env->t[1].width);
	while (i[0] >= 0 && i[0] < env->l.r[1] && i[0] <= i[1])
	{
		c[2] = (i[0] - start) * c[1];
		color = index_color(c[0], c[2], &(env->t[1]));
		my_put_pixel(&(env->i), env->nbray, i[0], color);
		i[0]++;
	}
	return ;
}

void	drawcole(struct s_env *env, int *i, double x)
{
	int		start;
	int		color;
	double	c[3];

	c[1] = ((float)env->t[2].height) / ((float)(i[1] - i[0]));
	start = i[0];
	i[0] = (i[0] < 0) ? 0 : i[0];
	c[0] = ((float)(x - ((int)x)) * (float)env->t[1].width);
	while (i[0] >= 0 && i[0] < env->l.r[1] && i[0] <= i[1])
	{
		c[2] = (i[0] - start) * c[1];
		color = index_color(c[0], c[2], &(env->t[2]));
		my_put_pixel(&(env->i), env->nbray, i[0], color);
		i[0]++;
	}
	return ;
}

void	drawcolw(struct s_env *env, int *i, double x)
{
	int		start;
	int		color;
	double	c[3];

	c[1] = ((float)env->t[3].height) / ((float)(i[1] - i[0]));
	start = i[0];
	i[0] = (i[0] < 0) ? 0 : i[0];
	c[0] = ((float)(x - ((int)x)) * (float)env->t[3].width);
	while (i[0] >= 0 && i[0] < env->l.r[1] && i[0] <= i[1])
	{
		c[2] = (i[0] - start) * c[1];
		color = index_color(c[0], c[2], &(env->t[3]));
		my_put_pixel(&(env->i), env->nbray, i[0], color);
		i[0]++;
	}
	return ;
}
