/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dra.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:41:40 by labintei          #+#    #+#             */
/*   Updated: 2021/05/05 13:59:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int			ca(struct s_env *env, double x, double y)
{
	if (x > 0 && x < env->xmax && y > 0 && y < env->ymax)
		return (1);
	return (0);
}

double		cald(struct s_env *env, double x, double y)
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

void		print_w(struct s_env *env, double *w)
{
	int		i[2];
	double	dist;
	double	d;
	double	hmur;

	d = sqrt(pow(fabs(w[0] - (int)w[0]) - (1 - fabs((1 - env->sp[2]) / 2)), 2) + pow(fabs(w[1] - (int)w[1]) - \
	(1 - fabs((1 - env->sp[3]) / 2)), 2));
	dist = sqrt(pow(w[0] - env->play.x, 2) + pow(w[1] - env->play.y, 2)) * env->sp[4];
	hmur = (double)env->l.r[1] / (dist);
	i[0] = (env->l.r[1] / 2) - (hmur / 2);
	i[1] = (env->l.r[1] / 2) + (hmur / 2);
	drawcol_sprite(env, i, d);
	return ;
}

void		stock_w(struct s_env *env, double **w, double *i)
{
	double		j[5];

	if(i[6] == -1)
		return ;
	j[0] = (i[6] == 1)? i[0] : i[2];
	j[1] = (i[6] == 1)? i[1] : i[3];
	j[2] = (env->sp[0] * env->sp[3] - (env->sp[2] * env->sp[1]));
	j[3] = ((env->play.y * env->sp[0] - env->play.x * env->sp[1]) * env->sp[2] - (env->sp[0] * (((int)j[1] + 0.5) * env->sp[2] - ((int)j[0] + 0.5) * env->sp[3]))) / j[2];
	j[4] = (-env->sp[1] * (((int)j[1] + 0.5) * env->sp[2] - ((int)j[0] + 0.5) * env->sp[3]) + (env->play.y * env->sp[0] - env->play.x * env->sp[1]) * env->sp[3]) / j[2];
	if ((int)j[3] != (int)j[0] || (int)j[4] != (int)j[1] || (sqrt(pow(j[3] - ((int)j[0] + 0.5), 2) + pow(j[4] - ((int)j[1] + 0.5), 2))) > 0.5)
		return ;
	w[(int)i[4]] = malloc((sizeof(double)) * 2);
	w[(int)i[4]][0] = j[3];
	w[(int)i[4]][1] = j[4];
	(i[4])++;
	return ;
}

void		checkboth(struct s_env *env, double *i, double **w)
{
	i[6] = -1;
	ajout_diff(env, i);
	i[6] = ((cald(env, i[0], i[1]) < i[5]) && env->l.map[(int)i[1]][(int)i[0]] == '2')? 1 : i[6];
	stock_w(env, w, i);
	i[6] = (cald(env, i[2], i[3]) < i[5] && env->l.map[(int)i[3]][(int)i[2]] == '2')? 2 : i[6];
	stock_w(env, w, i);
	if (cald(env, i[0], i[1]) < i[5] || cald(env, i[2], i[3]) < i[5])
		checkboth(env, i, w);
	return ;
}

void		dray_angle_sprite(struct s_env *env, double d)
{
	double	i[7];
	double	**w;

	i[4] = 0;
	i[5] = d;
	i[6] = -1;
	w = malloc(sizeof(double *) * (2 * (ceil(d + 1))));
	init_i(env, i);
	i[6] = (cald(env, i[0], i[1]) < d && env->l.map[(int)i[1]][(int)i[0]] == '2')? 1 : i[6];
	stock_w(env, w, i);
	i[6] = (cald(env, i[2], i[3]) < d && env->l.map[(int)i[3]][(int)i[2]] == '2')? 2 : i[6];
	stock_w(env, w, i);
	if ((cald(env, i[0], i[1]) < d) || (cald(env, i[2], i[3]) < d))
		checkboth(env, i, w);
	tri_w(env, w, i[4]);
	while (--(i[4]) != -1)
		print_w(env, w[(int)i[4]]);
	while (w[((int)++(i[4]))])
	{
		w[(int)i[4]][0] = 0;
		w[(int)i[4]][1] = 0;
		free(w[(int)i[4]]);
	}
	free(w);
	return ;
}
