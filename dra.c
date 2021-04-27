/************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dra.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:41:40 by labintei          #+#    #+#             */
/*   Updated: 2021/04/27 14:36:29 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

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

void		tri_w(struct s_env *env, double **w)
{
	double	temp[2];
	int		n;

	n = 0;
	while(w[n] && w[n + 1])
	{
		if((fabs(w[n][0] - env->play.x) + fabs(w[n][1] - env->play.y)) \
		> (fabs(w[n + 1][0] - env->play.x) + fabs(w[n + 1][1] - env->play.y)))
		{
			temp[0] = w[n + 1][0];
			temp[1] = w[n + 1][1];
			w[n + 1][0] = w[n][0];
			w[n + 1][1] = w[n][1];
			w[n][0] = temp[0];
			w[n][1] = temp[1];
		}
		n++;
	}
	return ;
}


void		drawcol_sprite1(struct s_env *env, int *i, double d)
{
	int		start;
	int		color;
	double	cx;
	double	cy;
	double	ch;
	int		hmur;

	hmur = i[1] - i[0];
	cx = d * env->t[4].width;
	ch = ((float)env->t[4].height)/ ((float)hmur);
	start = i[0];
	start = (start < 0)? 0 : start;
	while(start >= 0 && start < env->l.r[1] && start <= i[1])
	{
		cy = (start - i[0]) * ch;
		color = index_color(cx, cy, &(env->t[4]));
		if(color & 0x00FFFFF)
			my_put_pixel(&(env->i), env->nbray, start, color);
		start++;
	}
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

void		print_w(struct s_env *env, double *w, double a)
{
	int		i[2];
	double	dist;
	double	diffx;
	double	diffy;
	double	d;
	double	hmur;
	double		co;
	double		si;

	diffx = fabs(w[0] - (int)w[0]);
	diffy = fabs(w[1] - (int)w[1]);
	co = fabs((1 - cos(env->play.pa + M_PI/2)) /2);
	si = fabs((1 - sin(env->play.pa + M_PI/2)) /2);
	d = sqrt(pow(diffx - (1 - co), 2) + pow(diffy - (1 - si), 2));
	dist = sqrt(pow(w[0] - env->play.x, 2) + pow(w[1] - env->play.y, 2));
	dist *= (cos(env->play.pa - a) != 0)? cos(env->play.pa -a) : 1;
	hmur = (double)env->l.r[1] / (dist * 2);
	i[0] = (env->l.r[1]/2) - (hmur/2);
	i[1] = (env->l.r[1]/2) + (hmur/2);
	drawcol_sprite1(env,i,d);
	drawcarre(w[0] * env->pas, w[1]*env->pas, 3, env, create_trtgb(0, 120,140,130));
	return ;
}

void		stock_w(struct s_env *env, double **w,int *n, double x, double y, double a)
{
	double		fx;
	double		fy;
	double		de;
	double		f;

	de = (cos(a) * sin(env->play.pa + M_PI/2) - (cos(env->play.pa + M_PI/2) * sin(a)));
	fx = ((env->play.y * cos(a) - env->play.x * sin(a)) * cos(env->play.pa + M_PI/2) - (cos(a)*(((int)y + 0.5) * cos(env->play.pa + M_PI/2) - ((int)x + 0.5) * sin(env->play.pa + M_PI/2))))/ de;
	fy = (-sin(a) * (((int)y + 0.5) * cos(env->play.pa +M_PI/2) - ((int)x + 0.5) * sin(env->play.pa + M_PI/2)) + (env->play.y * cos(a) - env->play.x * sin(a)) * sin(env->play.pa + M_PI/2))/de;
	if((int)fx != (int)x || (int)fy != (int)y || (f = sqrt(pow(fx - ((int)x + 0.5), 2) + pow(fy - ((int)y + 0.5), 2))) > 0.5)
		return ;
	w[*n] = malloc((sizeof(double)) * 2);
	w[*n][0] = fx;
	w[*n][1] = fy;
	(*n)++;
	return ;
}

void		checkboth(struct s_env *env, double *i, double d, double a, int *n, double **w)
{
	ajout_diff(env, i);
	if(ca(env,i[0],i[1]))
		if(env->l.map[(int)i[1]][(int)i[0]] == '2' && cald_bis(env,i[0],i[1]) < d - 0.0001)
			stock_w(env, w, n, i[0], i[1], a);
	if(ca(env,i[2],i[3]))
		if(env->l.map[(int)i[3]][(int)i[2]] == '2' && cald_bis(env,i[2],i[3]) < d - 0.0001)
			stock_w(env, w, n, i[2], i[3], a);
	if(cald_bis(env,i[0],i[1]) < d - 0.0001  || cald_bis(env,i[2],i[3]) < d - 0.0001)
		checkboth(env, i, d ,a, n, w);
	return ;
}

void		free_w(double **w)
{
	int		n;

	n = -1;
	while(w[++n])
	{	
		w[n][0] = 0;
		w[n][1] = 0;
		free(w[n]);
	}
	return ;
}

void		dray_angle_sprite(struct s_env *env, double a, double d)
{
	double	i[4];
	double	**w;
	double	angle;
	int		n;

	angle = a;
	angle -= (a > 2 * M_PI)? 2*M_PI : 0;
	angle += (a < 0)? 2 * M_PI : 0;
	n = 0;
	w = malloc(sizeof(double*) * (2*(ceil(d + 1))));
	init_i(env,i);
	if(ca(env,i[0],i[1]))
		if(env->l.map[(int)i[1]][(int)i[0]] == '2' && cald_bis(env,i[0],i[1]) < d - 0.0001)
		{
			//i[0] += 0.00001;
			stock_w(env, w, &n, i[0], i[1], angle);
		}
	if(ca(env,i[2],i[3]))
		if(env->l.map[(int)i[3]][(int)i[2]] == '2' && cald_bis(env,i[2],i[3]) < d - 0.0001)
		{
			//i[3] += 0.00001;
			stock_w(env, w, &n, i[2], i[3], angle);
		}
	if((cald_bis(env, i[0], i[1]) <  d) || (cald_bis(env, i[2], i[3]) < d - 0.0001))
		checkboth(env,i,d,angle, &n, w);
	w[n] = 0;
	tri_w(env, w);
	n--;
	while(n != -1)
	{
		print_w(env, w[n], a);
		n--;
	}
	free_w(w);
	free(w);
	return ;
}
