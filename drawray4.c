/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawray4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 10:50:11 by labintei          #+#    #+#             */
/*   Updated: 2021/04/05 15:37:38 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void		init_i(struct s_env *env, double *i)
{
	i[0] = env->envi[0];
	i[1] = env->envi[1];
	i[2] = env->envi[2];
	i[3] = env->envi[3];
	return ;

}
void		maxxy(struct s_env *env, int *xmax, int *ymax)
{
	while(env->l.map[*ymax][*xmax] != '\0')
		(*xmax)++;
	while(env->l.map[*ymax] != 0)
		(*ymax)++;
	return ;
}

double		cald(double	x1, double x2, double y1, double y2)
{
	return(sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)));
}

void	check_vert(struct s_env *env,double *x, double *y)
{
	char	u;

	u = 0;
	while(*x >= 0 && *y >= 0 && *x < env->xmax && *y < env->ymax && u == 0)
	{
		(*x) += env->diff[0];
		(*y) += env->diff[1];
		if(*x > 0 && *x < env->xmax && *y > 0 && *y < env->ymax)
			u = (env->l.map[(int)(*y)][(int)(*x)] == '1')? 1 : 0;
	}
	return ;
}

void	check_hori(struct s_env *env,double *x,double *y)
{
	char	u;

	u = 0;
	while(*x >= 0 && *y >= 0 && *x < env->xmax && *y < env->ymax && u == 0)
	{
		(*x) += env->diff[2];
		(*y) += env->diff[3];
		if(*x > 0 && *x < env->xmax && *y > 0 && *y < env->ymax)
			u = (env->l.map[(int)(*y)][(int)(*x)] == '1')? 1 : 0;
	}
	return ;
}

void	dray(struct	s_env *env, double a)
{
	double	i[4];

	dvar(env, a);
	init_envi(env, a);
	init_i(env, i);
	if(a != 0 && a != M_PI)
	{
		if(i[0] > 0 && i[0] < env->xmax && i[1] > 0 && i[1] < env->ymax)
			if(env->l.map[(int)i[1]][(int)i[0]] != '1')
				check_hori(env, &(i[0]), &(i[1]));
	}
	if(a != env->var[3] && a != env->var[4])
	{
		if(i[2] > 0 && i[2] < env->xmax && i[3] > 0 && i[3] < env->ymax)
			if(env->l.map[(int)i[3]][(int)i[2]] != '1')
				check_vert(env, &(i[2]), &(i[3]));
	}
	f_compare(env, i[2], i[3], i[0], i[1], a);
	return;
}
