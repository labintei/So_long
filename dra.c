/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dra.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:41:40 by labintei          #+#    #+#             */
/*   Updated: 2021/04/09 16:14:42 by labintei         ###   ########.fr       */
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

void		drawcol_sprite(struct s_env *env,double x,int *i)
{
	int		start;
	int		color;
	double	xmur;
	double	hmur;
	double	ch;
	float	cx;
	float	cy;
	
	xmur = x - ((int)x);
	hmur = (i[0] - i[1]);
	cx = fabs(xmur * ((float)env->t[4].width));
	ch = fabs(((float)env->t[4].height / ((float)hmur)));
	start = i[0];
	start = (start < 0)? 0 : start;
	while(start >= 0 && start < env->l.r[1] && start <= i[1])
	{
		cy = (start - i[0])* ch;
		color = index_color(cx, cy,&(env->t[4]));
		my_put_pixel(&(env->i), env->nbray, start, color);
		start++;
	}
	return ;
}


void		draw_line_sprite_1(double x, double y,struct s_env *env,double a)
{
	double	dist;
	double	hmur;
	double	angle;
	int		i[2];

	angle = env->play.pa - a;
	angle -= (angle >= 2 * M_PI)? 2*M_PI : 0;
	angle += (angle < 0)? 2 * M_PI : 0;
	dist = cald_bis(env, x, y);
	dist *= (angle != M_PI/2 && angle != (3*M_PI/2))? cos(angle) : 1;
	hmur = (double)env->l.r[1] / dist;
	i[0] = (env->l.r[1]/2) - (hmur/2);
	i[1] = (env->l.r[1]/2) + (hmur/2);
	drawcol_sprite(env,y, i);
	return ;
}

void		draw_line_sprite(double x, double y,struct s_env *env,double a)
{
	double	dist;
	double	hmur;
	double	angle;
	int		i[2];

	angle = env->play.pa - a;
	angle -= (angle >= 2 * M_PI)? 2*M_PI : 0;
	angle += (angle < 0)? 2 * M_PI : 0;
	dist = cald_bis(env, x, y);
	dist *= (angle != M_PI/2 && angle != (3*M_PI/2))? cos(angle) : 1;
	hmur = (double)env->l.r[1] / dist;
	i[0] = (env->l.r[1]/2) - (hmur/2);
	i[1] = (env->l.r[1]/2) + (hmur/2);
	drawcol_sprite(env,x, i);
	return ;
}

void		draw_line_sprite_4(double x, double y,struct s_env *env,double a)
{
	double	dist;
	double	hmur;
	double	angle;
	int		i[2];

	angle = env->play.pa - a;
	angle -= (angle >= 2 * M_PI)? 2*M_PI : 0;
	angle += (angle < 0)? 2 * M_PI : 0;
	dist = cald_bis(env, x, y);
	dist *= (angle != M_PI/2 && angle != (3*M_PI/2))? cos(angle) : 1;
	hmur = (double)env->l.r[1] / dist;
	i[0] = (env->l.r[1]/2) - (hmur/2);
	i[1] = (env->l.r[1]/2) + (hmur/2);
	drawcol_sprite(env,y, i);
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
	double	testx;
	double	testy;

	init_stock_0(s);
	ajout_diff(env, i);
	if(a != 0 && a != M_PI)
		init_stock_1(i,s);
	if(a != env->var[3] && a != env->var[4])
		init_stock_2(i,s);
	if(cald_bis(env,i[0],i[1]) < d || cald_bis(env,i[2],i[3]) < d)
		checkboth(env, i, d, a);
	if(ca(env,s[0],s[1]))
		if(env->l.map[(int)s[1]][(int)s[0]] == '2' && cald_bis(env,s[0],s[1]) < d)
		{
			testy = s[0] - ((int)s[0]);
			drawcarre((((int)(s[0])) + 0.5 +((testy - 0.5) * cos(env->play.pa + M_PI/2))) * env->pas, (((int)s[1]) + 0.5  + ((testy - 0.5) * sin(env->play.pa + M_PI/2))) * env->pas, 5,env,create_trtgb(0,250,150,0));
			draw_line_sprite((((int)(s[0])) + 0.5 +((testy - 0.5) * cos(env->play.pa + M_PI/2))), (((int)s[1]) + 0.5  + ((testy - 0.5) * sin(env->play.pa + M_PI/2))),env,a); 

		}
	if(ca(env,s[2],s[3]))
		if(env->l.map[(int)s[3]][(int)s[2]] == '2' && cald_bis(env,s[2],s[3]) < d)
		{
			testx = s[3] - ((int)s[3]);
			drawcarre((((int)(s[2])) + 0.5 + ((testx - 0.5) * cos(env->play.pa + M_PI/2))) * env->pas, (((int)s[3])+ 0.5 + ((testx - 0.5) * sin(env->play.pa + M_PI/2))) * env->pas, 5,env,create_trtgb(0,0,150,0));
			draw_line_sprite_4((((int)(s[2])) + 0.5 + ((testx - 0.5) * cos(env->play.pa + M_PI/2))) , (((int)s[3])+ 0.5 + ((testx - 0.5) * sin(env->play.pa + M_PI/2))) ,env,a);

		}
	return ;
}

void		dray_angle_sprite(struct s_env *env, double a, double d)
{
	double	i[4];
	double	s[4];
	double	testx;
	double	testy;

	init_i(env,i);
	init_stock_0(s);
	if(a != 0 && a != M_PI)
		init_stock_1(i,s);
	if(a != env->var[3] && a != env->var[4])
		init_stock_2(i,s);
	if((cald_bis(env, i[0], i[1]) <  d) || (cald_bis(env, i[2], i[3]) < d))
		checkboth(env,i,d,a);
	if(ca(env,s[0],s[1]))
		if(env->l.map[(int)s[1]][(int)s[0]] == '2' && cald_bis(env,s[0],s[1]) < d)
		{
			testy = s[0] - ((int)s[0]);
			drawcarre((((int)(s[0])) + 0.5 +((testy - 0.5) * cos(env->play.pa + M_PI/2))) * env->pas, (((int)s[1]) + 0.5  + ((testy - 0.5) * sin(env->play.pa + M_PI/2))) * env->pas, 5,env,create_trtgb(0,250,150,0));
			draw_line_sprite((((int)(s[0])) + 0.5 +((testy - 0.5) * cos(env->play.pa + M_PI/2))), (((int)s[1]) + 0.5  + ((testy - 0.5) * sin(env->play.pa + M_PI/2))),env,a); 

		}
	if(ca(env,s[2],s[3]))
		if(env->l.map[(int)s[3]][(int)s[2]] == '2' && cald_bis(env,s[2],s[3]) < d)
		{
			testx = s[3] - ((int)s[3]);
			drawcarre((((int)(s[2])) + 0.5 + ((testx - 0.5) * cos(env->play.pa + M_PI/2))) * env->pas, (((int)s[3])+ 0.5 + ((testx - 0.5) * sin(env->play.pa + M_PI/2))) * env->pas, 5,env,create_trtgb(0,0,150,0));
			draw_line_sprite_4((((int)(s[2])) + 0.5 + ((testx - 0.5) * cos(env->play.pa + M_PI/2))) , (((int)s[3])+ 0.5 + ((testx - 0.5) * sin(env->play.pa + M_PI/2))) ,env,a);
		}
	return ;
}
