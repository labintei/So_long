/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawray4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 10:50:11 by labintei          #+#    #+#             */
/*   Updated: 2021/04/04 10:40:37 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"


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

void	init_first(struct	s_env *env, double **i, double a)
{
	*i[1] = (a > M_PI) ? ((int)env->play.y) - 0.00001 : ((int)env->play.y) + 1;
	*i[0] = (a != 0 && a != M_PI) ? env->play.x - (((env->play.y - *i[1])/sin(a)) * cos(a)) : 1;
	*i[2] = (a > env->var[4] && a < env->var[3]) ? ((int)env->play.x) - 0.00001 : ((int)env->play.x) + 1;
	*i[3] = (a != env->var[3] && a != env->var[4]) ? env->play.y - (((env->play.x - *i[2])/cos(a)) * sin(a)) : 1;
	printf("%f %f %f %f",(float)*i[0],(float)*i[1],(float)*i[2],(float)*i[3]);
	
	return ;
}

void	ft_free_i(double **i)
{
	*i[0] = 0;
	*i[1] = 0;
	*i[2] = 0;
	*i[3] = 0;
	return ;
}

void	dray(struct	s_env *env, double a)
{
	double	i[4];

	dvar(env, a);
	i[1] = (a > M_PI) ? ((int)env->play.y) - 0.00001 : ((int)env->play.y) + 1;
	i[0] = (a != 0 && a != M_PI) ? env->play.x - (((env->play.y - i[1])/sin(a)) * cos(a)) : 1;
	i[2] = (a > env->var[4] && a < env->var[3]) ? ((int)env->play.x) - 0.00001 : ((int)env->play.x) + 1;
	i[3] = (a != env->var[3] && a != env->var[4]) ? env->play.y - (((env->play.x - i[2])/cos(a)) * sin(a)) : 1;
	if(a != env->var[3] && a != env->var[4])
	{
		if(i[2] > 0 && i[2] < env->xmax && i[3] > 0 && i[3] < env->ymax)
			if(env->l.map[(int)i[3]][(int)i[2]] != '1')
				check_vert(env, &(i[2]), &(i[3]));
	}
	if(a != 0 && a != M_PI)
	{
		if(i[0] > 0 && i[0] < env->xmax && i[1] > 0 && i[1] < env->ymax)
			if(env->l.map[(int)i[1]][(int)i[0]] != '1')
				check_hori(env, &(i[0]), &(i[1]));
	}
	f_compare(env, i[2], i[3], i[0], i[1], a);
	return;
}
