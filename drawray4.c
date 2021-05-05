/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawray4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 10:50:11 by labintei          #+#    #+#             */
/*   Updated: 2021/05/05 13:20:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void		check_vert(struct s_env *env, double *x, double *y)
{
	char	u;

	u = 0;
	while (*x >= 0 && *y >= 0 && *x < env->xmax && *y < env->ymax && u == 0)
	{
		(*x) += env->diff[0];
		(*y) += env->diff[1];
		if (*x > 0 && *x < env->xmax && *y > 0 && *y < env->ymax)
			u = (env->l.map[(int)(*y)][(int)(*x)] == '1') ? 1 : 0;
	}
	return ;
}

void		check_hori(struct s_env *env, double *x, double *y)
{
	char	u;

	u = 0;
	while (*x >= 0 && *y >= 0 && *x < env->xmax && *y < env->ymax && u == 0)
	{
		(*x) += env->diff[2];
		(*y) += env->diff[3];
		if (*x > 0 && *x < env->xmax && *y > 0 && *y < env->ymax)
			u = (env->l.map[(int)(*y)][(int)(*x)] == '1') ? 1 : 0;
	}
	return ;
}

void		dray(struct s_env *env, double a)
{
	double	i[4];
	double	angle;

	angle = (a >= env->var[2]) ? a - env->var[2] : a;
	angle += (angle < 0) ? env->var[2] : 0;
	dvar(env, angle);
	init_envi(env, angle);
	init_i(env, i);
	if (angle != 0 && angle != M_PI)
	{
		if (i[0] > 0 && i[0] < env->xmax && i[1] > 0 && i[1] < env->ymax)
			if (env->l.map[(int)i[1]][(int)i[0]] != '1')
				check_hori(env, &(i[0]), &(i[1]));
	}
	if (angle != env->var[3] && angle != env->var[4])
	{
		if (i[2] > 0 && i[2] < env->xmax && i[3] > 0 && i[3] < env->ymax)
			if (env->l.map[(int)i[3]][(int)i[2]] != '1')
				check_vert(env, &(i[2]), &(i[3]));
	}
	f_compare(env, i, a);
	return ;
}
