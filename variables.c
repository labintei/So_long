/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 13:12:59 by user42            #+#    #+#             */
/*   Updated: 2021/05/05 15:50:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#define KEY_RIGHT 65361
#define KEY_LEFT 65363
#define KEY_ESC 65307
#define KEY_W 119
#define KEY_S 115

void		init_spe(struct s_env *env, int keycode, double *i)
{
	if (keycode == KEY_RIGHT)
		env->play.pa -= env->rot;
	if (keycode == KEY_LEFT)
		env->play.pa += env->rot;
	if (keycode == KEY_ESC)
		destroy_ta_vie(env);
	env->sp[2] = cos(env->play.pa + M_PI / 2);
	env->sp[3] = sin(env->play.pa + M_PI / 2);
	i[0] = cos(env->play.pa) / 20;
	i[1] = sin(env->play.pa) / 20;
	i[2] = env->sp[2] / 20;
	i[3] = env->sp[3] / 20;
	if (keycode == KEY_W && env->l.map[(int)(env->play.y + i[1])][(int)\
	(env->play.x + i[0])] != '1')
	{
		env->play.x += i[0];
		env->play.y += i[1];
	}
	if (keycode == KEY_S && env->l.map[(int)(env->play.y - i[1])][(int)\
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
