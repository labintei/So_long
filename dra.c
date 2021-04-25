/************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dra.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:41:40 by labintei          #+#    #+#             */
/*   Updated: 2021/04/22 17:02:17 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "map.h"


void		init_stock_0(double *s)
{
	s[0] = -1;
	s[1] = -1;
	s[2] = -1;
	s[3] = -1;
	return ;
}

void		init_stock_1(double *i,double *s)
{
	s[0] = i[0];
	s[1] = i[1];
	return ;
}

void		init_stock_2(double *i,double *s)
{
	s[2] = i[2];
	s[3] = i[3];
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

int			ca(struct s_env *env, double x,double y)
{
	if(x > 0 && x < env->xmax && y > 0 && y < env->ymax)
		return(1);
	return(0);
}

double		cald_bis(struct s_env *env, double x, double y)
{
	return(sqrt(pow(x - env->play.x, 2) + pow(y - env->play.y, 2)));
}

void		drawcol_sprite(struct s_env *env, int *i)
{
	int		start;
	int		color;
	
	start = i[0];
	start = (start < 0)? 0 : start;
	while(start >= 0 && start < env->l.r[1] && start <= i[1])
	{
		color = create_trtgb(0,150,0,0);
		my_put_pixel(&(env->i), env->nbray, start, color);
		start++;
	}
	return ;
}


void		drawcol_sprite1(struct s_env *env, int *i)
{
	int		start;
	int		color;
	
	start = i[0];
	start = (start < 0)? 0 : start;
	while(start >= 0 && start < env->l.r[1] && start <= i[1])
	{
		color = create_trtgb(0,0,150,0);
		my_put_pixel(&(env->i), env->nbray, start, color);
		start++;
	}
	return ;
}

void		draw_line_sprite_5(double x, double y,struct s_env *env,double a)
{
	double	dist;
	double	hmur;
	int		i[2];
	double		co;
	double		si;
	
	double		fx;
	double		fy;
	double		de;

	co = fabs((1 - cos(env->play.pa + M_PI/2)) /2);
	si = fabs((1 - sin(env->play.pa + M_PI/2)) /2);

	de = (cos(a) * sin(env->play.pa + M_PI/2) - (cos(env->play.pa + M_PI/2) * sin(a)));
	fx = ((env->play.y * cos(a) - env->play.x * sin(a)) * cos(env->play.pa + M_PI/2) - (cos(a)*(((int)y + 0.5) * cos(env->play.pa + M_PI/2) - ((int)x + 0.5) * sin(env->play.pa + M_PI/2))))/ de;
	fy = (-sin(a) * (((int)y + 0.5) * cos(env->play.pa +M_PI/2) - ((int)x + 0.5) * sin(env->play.pa + M_PI/2)) + (env->play.y * cos(a) - env->play.x * sin(a)) * sin(env->play.pa + M_PI/2))/de;

	double	diffx;
	double	diffy;
	diffx = fabs(fx - (int)fx);
	diffy = fabs(fy - (int)fy);

	if((int)fx != (int)(x) || (int)fy != (int)y || sqrt(pow(diffx - 0.5,2) + pow(diffy - 0.5,2)) > 0.5)
		return ;
	
	dist = sqrt(pow(fx - env->play.x, 2) + pow(fy - env->play.y, 2));
	dist *= cos(env->play.pa - a);
//	drawcarre(fx * env->pas, fy * env->pas, 3,env, create_trtgb(0,120,60,165));
	hmur = (double)env->l.r[1] / dist;
	i[0] = (env->l.r[1]/2) - (hmur/2);
	i[1] = (env->l.r[1]/2) + (hmur/2);
	drawcol_sprite1(env,i);
	return ;
}

void		dvar(struct s_env *env, double a)
{
	env->diff[0] = (a < (3 * M_PI/2) && a > (M_PI/2))? -1 : 1;
	env->diff[1] = (a != 0 && a != M_PI) ? (((a < (3 * M_PI/2) && a > (M_PI/2))? -1 : 1) / cos(a)) * sin(a) : 0;
	env->diff[2] = (a != M_PI/2 && a != (3 * M_PI/2)) ? ((((a > 0 && a < M_PI)? 1 : -1) / sin(a)) * cos(a)) : 0;
	env->diff[3] = (a > 0 && a < M_PI)? 1 : -1;
	return ;
}

void		checkboth(struct s_env *env, double *i, double d, double a)
{
	double	s[4];
	double	x;
	double y;

	double e;
	e = 0;
	init_stock_0(s);
	ajout_diff(env, i);
	init_stock_1(i,s);
	init_stock_2(i,s);
	if(cald_bis(env,i[0],i[1]) < d  || cald_bis(env,i[2],i[3]) < d)
		checkboth(env, i, d, a);
	if(ca(env,s[0],s[1]))
		if(env->l.map[(int)s[1]][(int)s[0]] == '2' && cald_bis(env,s[0],s[1]) < d)
		{
			x = (s[0] - ((int)s[0]));
			//drawcarre(s[0] * env->pas, s[1] * env->pas, 4, env ,create_trtgb(0,0,0,200));
			draw_line_sprite_5(s[0] , s[1] , env, a);
		}
	/* AFFICHAGE OK*/
	if(ca(env,s[2],s[3]))
		if(env->l.map[(int)s[3]][(int)s[2]] == '2' && cald_bis(env,s[2],s[3]) < d)
		{
			e = (a > M_PI/2 && a < (3*M_PI/2))? -1 : 0;
			y = (s[3] - (int)s[3]);
			//drawcarre(s[2] * env->pas, s[3] * env->pas, 2, env, create_trtgb(0,150,20,30));
			draw_line_sprite_5(s[2],  s[3], env, a);
		}
	return ;
}

void		init_i_2(struct s_env *env, double *i, double a)
{
	a += (a < 0)? 2 * M_PI : 0;
	a -= (a > 2 * M_PI)? 2 * M_PI : 0;
	i[1] = (a > M_PI)? ((int)env->play.y) - 0.00001 : ((int)env->play.y) + 1;
	i[0] = (a != 0 && a != M_PI)? (env->play.x - (((env->play.y - i[1]) / sin(a)) * cos(a))) : 0;
	i[2] = (a > env->var[4] && a < env->var[3])? ((int)env->play.x) - 0.00001 : ((int)env->play.x) + 1;
	i[3] = (a != env->var[3] && a != env->var[4])? env->play.y - (((env->play.x - i[2] )/cos(a)) * sin(a)) : 0;
	return ;
}


void		dray_angle_sprite(struct s_env *env, double a, double d)
{
	double	i[4];
	double	s[4];
	double	angle;
	double	x;
	double	y;

	angle = a;
	angle -= (a > 2 * M_PI)? 2*M_PI : 0;
	angle += (a < 0)? 2 * M_PI : 0;


	init_i(env,i);
	init_stock_0(s);
	init_stock_1(i,s);
	init_stock_2(i,s);
	if((cald_bis(env, i[0], i[1]) <  d) || (cald_bis(env, i[2], i[3]) < d))
		checkboth(env,i,d,angle);
	if(ca(env,s[0],s[1]))
		if(env->l.map[(int)s[1]][(int)s[0]] == '2' && cald_bis(env,s[0],s[1]) < d)
		{
				x = (s[0] - ((int)s[0]));
				//drawcarre(s[0] * env->pas, s[1] * env->pas, 2, env, create_trtgb(0,50,20,30));
				draw_line_sprite_5(s[0] , s[1], env, angle);
		}
	/* AFFICHAGE OK*/
	
	if(ca(env,s[2],s[3]))
		if(env->l.map[(int)s[3]][(int)s[2]] == '2' && cald_bis(env,s[2],s[3]) < d - 0.00001)
		{
			y = (s[3] - (int)s[3]);
			//drawcarre(s[2] * env->pas, s[3] * env->pas, 2, env, create_trtgb(0,150,20,30));
			draw_line_sprite_5(s[2],  s[3] , env, angle);

		}
	return ;
}
