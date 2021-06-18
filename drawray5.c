/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawray5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 10:50:11 by labintei          #+#    #+#             */
/*   Updated: 2021/06/18 12:37:15 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	f_compare(struct s_env *env, double *i, char *c, double a)
{
	double		r[4];

	r[0] = a;
	if (c[0] == 2 && c[1] == 2 && (fabs(i[0] - env->play.x) + fabs(i[1] - \
	env->play.y)) > (fabs(i[2] - env->play.x) + fabs(i[3] - env->play.y)))
		c[0] = 0;
	else if (c[0] == 2 && c[1] == 2)
		c[1] = 0;
	couleur_r(r, i, env, c);
	drawcol1(env, r);
	return (dray_angle_sprite(env, r[1]));
}

void	drawcol1(struct s_env *env, double *r)
{
	double	hmur;
	int		i[2];
	double	dist;

	dist = r[1] * env->sp[4];
	hmur = (int)(env->l.r[1] / (dist));
	i[0] = (env->l.r[1] / 2) - (hmur / 2);
	i[1] = (env->l.r[1] / 2) + (hmur / 2);
	if (env->c == 0 || env->c == 1)
		drawcols(env, i, r[2]);
	else
		drawcols(env, i, r[3]);
	return ;
}

void	dvarconst(struct s_env *env)
{
	env->sp[2] = cos(env->play.pa + M_PI / 2);
	env->sp[3] = sin(env->play.pa + M_PI / 2);
	env->var[0] = (((M_PI / 2)) / env->l.r[0]);
	env->var[1] = (env->l.r[0] / 2) * env->var[0];
	env->var[2] = 2 * M_PI;
	env->var[3] = 3 * (M_PI / 2);
	env->var[4] = M_PI / 2;
	env->rot = (2 * M_PI) / 360;
	return ;
}

void	stock_drawfov(struct s_env *env)
{
	double	i[3];
	double	*l;
	int		n;

	l = malloc(sizeof(double) * (((int)(env->l.r[0] / 2)) + 2));
	init_p(env);
	env->fov = malloc(sizeof(double) * ((env->l.r[0] / 2) + 2));
	if (!l || !(env->fov))
		return ;
	i[1] = M_PI / 4;
	l[0] = 0;
	n = -1;
	i[0] = env->l.r[0] / (2 * tan(M_PI / 4));
	while (++n <= (env->l.r[0] / 2))
	{
		l[n] = i[1] - fabs((atan(abs(((int)env->l.r[0] / 2) - n) / i[0])));
		i[1] -= fabs(l[n]);
	}
	n = -1;
	while (++n <= ((int)(env->l.r[0] / 2)))
	{
		env->fov[n] = l[n];
		l[n] = 0;
	}
	free(l);
}

void	drawfov_bis(struct s_env *env)
{
	double	angle;
	int		n;

	if (env->play.pa < 0)
		env->play.pa += 2 * M_PI;
	if (env->play.pa > 2 * M_PI)
		env->play.pa -= 2 * M_PI;
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
}
