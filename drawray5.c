/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawray5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 10:50:11 by labintei          #+#    #+#             */
/*   Updated: 2021/05/05 14:01:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void		f_compare(struct s_env *env, double *i, double a)
{
	double		o;
	double		r[4];

	r[0] = a;
	if (cald(env, i[2], i[3]) < cald(env, i[0], i[1]) || a == 0 || a == M_PI)
	{
		env->c = (i[2] > env->play.x) ? 1 : 2;
		r[1] = (cald(env, i[2], i[3]));
		r[2] = i[2];
		r[3] = i[3];
		o = r[1];
		drawcol1(env, r);
		return (dray_angle_sprite(env, o));
	}
	if (cald(env, i[2], i[3]) >= cald(env, i[0], i[1])\
	|| a == env->var[3] || a == env->var[4])
	{
		env->c = (i[1] > env->play.y) ? 3 : 4;
		r[1] = (cald(env, i[0], i[1]));
		r[2] = i[0];
		r[3] = i[1];
		o = r[1];
		drawcol1(env, r);
		return (dray_angle_sprite(env, o));
	}
	return ;
}

void		drawcol1(struct s_env *env, double *r)
{
	double	hmur;
	int		i[2];
	double	dist;

	dist = r[1] * env->sp[4];
	hmur = (int)(env->l.r[1] / (dist));
	i[0] = (env->l.r[1] / 2) - (hmur / 2);
	i[1] = (env->l.r[1] / 2) + (hmur / 2);
	if (env->c == 1)
		drawcoln(env, i, r[3]);
	if (env->c == 2)
		drawcols(env, i, r[3]);
	if (env->c == 3)
		drawcole(env, i, r[2]);
	if (env->c == 4 || env->c == 0)
		drawcolw(env, i, r[2]);
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
