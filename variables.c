/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 13:12:59 by user42            #+#    #+#             */
/*   Updated: 2021/05/17 11:29:45 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	init_spe(struct s_env *env, double *i)
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
	if (env->key[1] && env->l.map[(int)(env->play.y + i[1])][(int)(env->play.\
	x + i[0])] != '1')
	{
		env->play.x += i[0];
		env->play.y += i[1];
	}
	if (env->key[3] && env->l.map[(int)(env->play.y - i[1])][(int)(
				env->play.x - i[0])] != '1')
	{
		env->play.x -= i[0];
		env->play.y -= i[1];
	}
}

void	init_envi(struct s_env	*env, double a)
{
	env->sp[0] = cos(a);
	env->sp[1] = sin(a);
	env->sp[4] = 1;
	if (cos(env->play.pa - a) != 0)
		env->sp[4] = cos(env->play.pa - a);
	env->envi[1] = ((int)env->play.y) + 1;
	if (a > M_PI)
		env->envi[1] = ((int)env->play.y) - 0.00001;
	env->envi[0] = 0;
	if (a != 0 && a != M_PI)
		env->envi[0] = (env->play.x - ((env->play.y - env->envi[1]) / \
					env->sp[1] * env->sp[0]));
	env->envi[2] = ((int)env->play.x) + 1;
	if (a > env->var[4] && a < env->var[3])
		env->envi[2] = ((int)env->play.x) - 0.00001;
	env->envi[3] = 0;
	if (a != env->var[3] && a != env->var[4])
		env->envi[3] = env->play.y - ((env->play.x - env->envi[2]) / \
		env->sp[0]) * env->sp[1];
	return ;
}

void	ajout_diff(struct s_env *env, double *i)
{
	i[0] += env->diff[2];
	i[1] += env->diff[3];
	i[2] += env->diff[0];
	i[3] += env->diff[1];
	return ;
}

void	dvar(struct s_env *env, double a)
{
	env->diff[0] = 1;
	if (a < (3 * M_PI / 2) && a > (M_PI / 2))
		env->diff[0] = -1;
	env->diff[1] = 0;
	if (a != 0 && a != M_PI)
		env->diff[1] = (env->diff[0] / cos(a)) * sin(a);
	env->diff[3] = -1;
	if (a > 0 && a < M_PI)
		env->diff[3] = 1;
	env->diff[2] = 0;
	if (a != M_PI / 2 && a != (3 * M_PI / 2))
		env->diff[2] = ((env->diff[3]) / sin(a)) * cos(a);
	init_envi(env, a);
	return ;
}

void	init_i(struct s_env *env, double *i)
{
	i[0] = env->envi[0];
	i[1] = env->envi[1];
	i[2] = env->envi[2];
	i[3] = env->envi[3];
	return ;
}
