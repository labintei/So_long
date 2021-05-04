/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dra.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:41:40 by labintei          #+#    #+#             */
/*   Updated: 2021/04/30 14:11:08 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void		ajout_diff(struct s_env *env, double *i)
{
	i[0] += env->diff[2];
	i[1] += env->diff[3];
	i[2] += env->diff[0];
	i[3] += env->diff[1];
	return ;
}

int			ca(struct s_env *env, double x, double y)
{
	if (x > 0 && x < env->xmax && y > 0 && y < env->ymax)
		return (1);
	return (0);
}

double		cald_bis(struct s_env *env, double x, double y)
{
	return (sqrt(pow(x - env->play.x, 2) + pow(y - env->play.y, 2)));
}

void		tri_w(struct s_env *env, double **w, int n)
{
	double	temp[2];
	int		d;
	int		o;

	w[n] = 0;
	o = 0;
	d = 0;
	while (w[o])
	{
		d = 0;
		while (w[d] && w[d + 1])
		{
			if ((fabs(w[d][0] - env->play.x) + fabs(w[d][1] - env->play.y)) \
			> (fabs(w[d + 1][0] - env->play.x) + fabs(w[d + 1][1] - env->play.y)))
			{
				temp[0] = w[d + 1][0];
				temp[1] = w[d + 1][1];
				w[d + 1][0] = w[d][0];
				w[d + 1][1] = w[d][1];
				w[d][0] = temp[0];
				w[d][1] = temp[1];
			}
			d++;
		}
		o++;
	}
	return ;
}

void		drawcol_sprite1(struct s_env *env, int *i, double d)
{
	double	c[3];
	int		start;
	int		color;

	c[0] = d * env->t[4].width;
	c[1] = ((float)env->t[4].height) / ((float)(i[1] - i[0]));
	start = i[0];
	start = (start < 0) ? 0 : start;
	while (start >= 0 && start < env->l.r[1] && start <= i[1])
	{
		c[2] = (start - i[0]) * c[1];
		color = index_color(c[0], c[2], &(env->t[4]));
		if (color & 0x00FFFFF)
			my_put_pixel(&(env->i), env->nbray, start, color);
		start++;
	}
	return ;
}

void		dvar(struct s_env *env, double a)
{
	env->diff[0] = (a < (3 * M_PI / 2) && a > (M_PI / 2)) ? -1 : 1;
	env->diff[1] = (a != 0 && a != M_PI) ? (((a < (3 * M_PI / 2) && a > (M_PI / 2)) ? -1 : 1) / cos(a)) * sin(a) : 0;
	env->diff[2] = (a != M_PI / 2 && a != (3 * M_PI / 2)) ? ((((a > 0 && a < M_PI) ? 1 : -1) / sin(a)) * cos(a)) : 0;
	env->diff[3] = (a > 0 && a < M_PI) ? 1 : -1;
	return ;
}

void		print_w(struct s_env *env, double *w, double a)
{
	int		i[2];
	double	dist;
	double	d;
	double	hmur;

	d = sqrt(pow(fabs(w[0] - (int)w[0]) - (1 - fabs((1 - cos(env->play.pa + \
	M_PI / 2)) / 2)), 2) + pow(fabs(w[1] - (int)w[1]) - \
	(1 - fabs((1 - sin(env->play.pa + M_PI / 2)) / 2)), 2));
	dist = sqrt(pow(w[0] - env->play.x, 2) + pow(w[1] - env->play.y, 2));
	dist *= (cos(env->play.pa - a) != 0) ? cos(env->play.pa - a) : 1;
	hmur = (double)env->l.r[1] / (dist);
	i[0] = (env->l.r[1] / 2) - (hmur / 2);
	i[1] = (env->l.r[1] / 2) + (hmur / 2);
	drawcol_sprite1(env, i, d);
	return ;
}

void		stock_w(struct s_env *env, double **w, int *n, double x, double y)
{
	double		fx;
	double		fy;
	double		de;
	double		f;

	de = (env->sp[0] * env->sp[3] - (env->sp[2] * env->sp[1]));
	fx = ((env->play.y * env->sp[0] - env->play.x * env->sp[1]) * env->sp[2] - (env->sp[0] * (((int)y + 0.5) * env->sp[2] - ((int)x + 0.5) * env->sp[3]))) / de;
	fy = (-env->sp[1] * (((int)y + 0.5) * env->sp[2] - ((int)x + 0.5) * env->sp[3]) + (env->play.y * env->sp[0] - env->play.x * env->sp[1]) * env->sp[3]) / de;
	if ((int)fx != (int)x || (int)fy != (int)y || (f = sqrt(pow(fx - ((int)x + 0.5), 2) + pow(fy - ((int)y + 0.5), 2))) > 0.5)
		return ;
	w[*n] = malloc((sizeof(double)) * 2);
	w[*n][0] = fx;
	w[*n][1] = fy;
	(*n)++;
	return ;
}

void		checkboth(struct s_env *env, double *i, double d, double a, int *n, double **w)
{
	ajout_diff(env, i);
	if (ca(env, i[0], i[1]))
		if (env->l.map[(int)i[1]][(int)i[0]] == '2' && cald_bis(env, i[0], i[1]) < d)
			stock_w(env, w, n, i[0], i[1]);
	if (ca(env, i[2], i[3]))
		if (env->l.map[(int)i[3]][(int)i[2]] == '2' && cald_bis(env, i[2], i[3]) < d)
			stock_w(env, w, n, i[2], i[3]);
	if (cald_bis(env, i[0], i[1]) < d - 0.0001  || cald_bis(env, i[2], i[3]) < d)
		checkboth(env, i, d, a, n, w);
	return ;
}

void		dray_angle_sprite(struct s_env *env, double a, double d)
{
	double	i[4];
	double	**w;
	int		n;

	n = 0;
	w = malloc(sizeof(double *) * (2 * (ceil(d + 1))));
	init_i(env, i);
	if (cald_bis(env, i[0], i[1]) < d && env->l.map[(int)i[1]][(int)i[0]] == '2')
		stock_w(env, w, &n, i[0], i[1]);
	if (cald_bis(env, i[2], i[3]) < d && env->l.map[(int)i[3]][(int)i[2]] == '2')
		stock_w(env, w, &n, i[2], i[3]);
	if ((cald_bis(env, i[0], i[1]) < d) || (cald_bis(env, i[2], i[3]) < d))
		checkboth(env, i, d, a, &n, w);
	tri_w(env, w, n);
	while (--n != -1)
		print_w(env, w[n], a);
	while (w[++n])
	{
		w[n][0] = 0;
		w[n][1] = 0;
		free(w[n]);
	}
	free(w);
	return ;
}
