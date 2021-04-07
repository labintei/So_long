/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:41:40 by labintei          #+#    #+#             */
/*   Updated: 2021/04/05 17:32:08 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "map.h"

void		init_envi(struct	s_env *env, double a)
{
	env->envi[1] = (a > M_PI) ? ((int)env->play.y) - 0.00001 : ((int)env->play.y) + 1;
	env->envi[0] = (a != 0 && a != M_PI) ? (env->play.x - (((env->play.y - env->envi[1])/sin(a)) * cos(a))) : 0;
	env->envi[2] = (a > env->var[4] && a < env->var[3]) ? ((int)env->play.x) - 0.000001 : ((int)env->play.x) + 1;
	env->envi[3] = (a != env->var[3] && a!= env->var[4]) ? env->play.y - (((env->play.x - env->envi[2])/cos(a)) * sin(a)) : 0;
	return ;
}
