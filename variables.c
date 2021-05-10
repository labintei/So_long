/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 13:12:59 by user42            #+#    #+#             */
/*   Updated: 2021/05/10 09:40:58 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void		init_spe(struct s_env *env, double *i)
{
	if (env->key[4])
		env->play.pa -= env->rot * 2;
	if (env->key[5])
		env->play.pa += env->rot * 2;
	if (env->key[6])
		destroy_ta_vie(env);
	env->sp[2] = cos(env->play.pa + M_PI / 2);
	env->sp[3] = sin(env->play.pa + M_PI / 2);
	i[0] = cos(env->play.pa) / 7;
	i[1] = sin(env->play.pa) / 7;
	i[2] = env->sp[2] / 7;
	i[3] = env->sp[3] / 7;
	if (env->key[1] && env->l.map[(int)(env->play.y + i[1])][(int)\
	(env->play.x + i[0])] != '1')
	{
		env->play.x += i[0];
		env->play.y += i[1];
	}
	if (env->key[3] && env->l.map[(int)(env->play.y - i[1])][(int)\
	(env->play.x - i[0])] != '1')
	{
		env->play.x -= i[0];
		env->play.y -= i[1];
	}
}

void		init_envi(struct s_env	*env, double a)
{
	env->sp[0] = cos(a);
	env->sp[1] = sin(a);
	env->sp[4] = (cos(env->play.pa - a) != 0) ? cos(env->play.pa - a) : 1;
	env->envi[1] = (a > M_PI) ? ((int)env->play.y) - 0.00001 : \
	((int)env->play.y) + 1;
	env->envi[0] = (a != 0 && a != M_PI) ? (env->play.x - \
	((env->play.y - env->envi[1]) / env->sp[1] * env->sp[0])) : 0;
	env->envi[2] = (a > env->var[4] && a < env->var[3]) ? \
	((int)env->play.x) - 0.00001 : ((int)env->play.x) + 1;
	env->envi[3] = (a != env->var[3] && a != env->var[4]) ?\
	env->play.y - ((env->play.x - env->envi[2]) / env->sp[0]) * env->sp[1] : 0;
	return ;
}

void		ajout_diff(struct s_env *env, double *i)
{
	i[0] += env->diff[2];
	i[1] += env->diff[3];
	i[2] += env->diff[0];
	i[3] += env->diff[1];
	return ;
}

void		dvar(struct s_env *env, double a)
{
	env->diff[0] = (a < (3 * M_PI / 2) && a > (M_PI / 2)) ? -1 : 1;
	env->diff[1] = (a != 0 && a != M_PI) ? (env->diff[0] / cos(a)) * sin(a) : 0;
	env->diff[3] = (a > 0 && a < M_PI) ? 1 : -1;
	env->diff[2] = (a != M_PI / 2 && a != (3 * M_PI / 2)) ? \
	((env->diff[3]) / sin(a)) * cos(a) : 0;
	return ;
}

void		init_i(struct s_env *env, double *i)
{
	i[0] = env->envi[0];
	i[1] = env->envi[1];
	i[2] = env->envi[2];
	i[3] = env->envi[3];
	return ;
}
