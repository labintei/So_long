/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawray5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 10:50:11 by labintei          #+#    #+#             */
/*   Updated: 2021/04/04 13:08:38 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int			index_color(int x, int y, struct s_texture *text)
{
	int		index;

	index = (y * text->line_lenght + x * (text->bits_per_pixels / 8));
	return(((int *)text->addr)[index/4]);
}


void		f_load_texture(struct	s_env *env)
{
	/* NORTH */
	env->t[0].img = mlx_xpm_file_to_image(env->p.mlx, env->l.no, &(env->t[0].width), &(env->t[0].height));
	env->t[0].addr = mlx_get_data_addr(env->t[0].img, &(env->t[0].bits_per_pixels), &(env->t[0].line_lenght), &(env->t[0].endian));
	/* SOUTH*/
	env->t[1].img = mlx_xpm_file_to_image(env->p.mlx, env->l.so, &(env->t[1].width), &(env->t[1].height));
	env->t[1].addr = mlx_get_data_addr(env->t[1].img, &(env->t[1].bits_per_pixels), &(env->t[1].line_lenght), &(env->t[1].endian));
	/* WEST*/
	env->t[2].img = mlx_xpm_file_to_image(env->p.mlx, env->l.we, &(env->t[2].width), &(env->t[2].height));
	env->t[2].addr = mlx_get_data_addr(env->t[2].img, &(env->t[2].bits_per_pixels), &(env->t[2].line_lenght), &(env->t[2].endian));
	/* EAST*/
	env->t[3].img = mlx_xpm_file_to_image(env->p.mlx, env->l.ea, &(env->t[3].width), &(env->t[3].height));
	env->t[3].addr = mlx_get_data_addr(env->t[3].img, &(env->t[3].bits_per_pixels), &(env->t[3].line_lenght), &(env->t[3].endian));
	/* SPRITE*/
	env->t[4].img = mlx_xpm_file_to_image(env->p.mlx, env->l.s, &(env->t[4].width), &(env->t[4].height));
	env->t[4].addr = mlx_get_data_addr(env->t[4].img, &(env->t[4].bits_per_pixels), &(env->t[4].line_lenght), &(env->t[4].endian));
	return ;
}

void		f_compare(struct s_env *env, double x1,double y1,double x, double y, double a)
{
	double		fin;
	double		o;
	int			color;

	if(cald(x1, env->play.x, y1, env->play.y) < cald(x, env->play.x, y, env->play.y) || \
	a == 0 || a == M_PI)
	{
		color = (x1 > env->play.x)? 1 : 2;
		fin = (cald(x1, env->play.x,y1, env->play.y));
		o = fin;
		drawcol1(env, &fin, a, color, x1, y1);
		return(dray_angle_sprite(env,a, o));
	}
	if(cald(x1, env->play.x, y1, env->play.y) >= cald(x, env->play.x, y, env->play.y) || \
	a == env->var[3] || a == env->var[4])
	{
		color = (y > env->play.y)? 3 : 4;
		fin = (cald(x, env->play.x, y, env->play.y));
		o = fin;
		drawcol1(env, &fin, a, color, x, y);
		return(dray_angle_sprite(env,a, o));
	}
	return ;
}

void	drawcol1(struct	s_env *env, double *d, double a, int color, double x, double y)
{
	double	hmur;
	int		i[2];
	double	angle;

	angle = env->play.pa - a;
	angle -= (angle >= 2 * M_PI)? 2*M_PI: 0;
	angle += (angle < 0)? 2*M_PI : 0;
	*d = *d * cos(angle);
	hmur = (double)env->l.r[1] / *d;
	i[0] = (env->l.r[1]/2) - (hmur / 2);
	i[1] = (env->l.r[1]/2) + (hmur / 2);
	drawcol2(env, i, color,x,y);
	return	;
}

void	dvarconst(struct s_env *env)
{
	env->var[0] = ((M_PI * 2) / 360) * 90 / env->l.r[0];
	env->var[1] = ((int)env->l.r[0]/2) * env->var[0];
	env->var[2] = 2 * M_PI;
	env->var[3] = 3 * (M_PI/2);
	env->var[4] = M_PI/2;
	return ;
}


void	drawfov(struct	s_env *env)
{
	double	angle;
	int			i;

	env->nbray = 0;
	angle = env->play.pa - env->var[1];
	i = 0;
	while(env->nbray < (env->l.r[0]))
	{	
		angle -= (angle >= env->var[2])? env->var[2]: 0;
		angle += (angle < 0)? env->var[2] : 0;
		dray(env,angle);
		angle += env->var[0];
		env->nbray++;
	}
	return ;
}

void	drawcolN(struct	s_env *env, int *i,double y)
{
	double		ymur;
	double		ch;
	int		hmur;
	int		start;
	int		color;

	float	cx;
	float	cy;

	ymur = y - ((int)y);
	hmur = (i[1] - i[0]);
	cx = ((float)env->t[0].width) / ((float)hmur);
	ch = ((float)env->t[0].height) / ((float)hmur);
	start = i[0];
	i[0] = (i[0] < 0)? 0 : i[0];
	cx = ((float)ymur * (float)env->t[0].width);
	while(i[0] >= 0 && i[0] < env->l.r[1] && i[0] <= i[1])
	{
		cy = (i[0] - start) * ch;
		color = index_color( cx , cy, &(env->t[0]));
		my_put_pixel(&(env->i),env->nbray,i[0], color);
		i[0]++;
	}
	return ;
}

void	drawcolS(struct	s_env *env, int *i,double y)
{	
	double		ymur;
	double		ch;
	int		hmur;
	int		start;
	int		color;

	float	cx;
	float	cy;

	ymur = y - ((int)y);
	hmur = (i[1] - i[0]);
	cx = ((float)env->t[1].width) / ((float)hmur);
	ch = ((float)env->t[1].height) / ((float)hmur);
	start = i[0];
	i[0] = (i[0] < 0)? 0 : i[0];
	cx = ((float)ymur * (float)env->t[1].width);
	while(i[0] >= 0 && i[0] < env->l.r[1] && i[0] <= i[1])
	{
		cy = (i[0] - start) * ch;
		color = index_color( cx , cy, &(env->t[1]));
		my_put_pixel(&(env->i),env->nbray,i[0], color);	
		i[0]++;
	}
	return ;
}

void	drawcolE(struct	s_env *env, int *i, double x)
{
	double		ymur;
	double		ch;
	int		hmur;
	int		start;
	int		color;

	float	cx;
	float	cy;

	ymur = x - ((int)x);
	hmur = (i[1] - i[0]);
	cx = ((float)env->t[2].width) / ((float)hmur);
	ch = ((float)env->t[2].height) / ((float)hmur);
	start = i[0];
	i[0] = (i[0] < 0)? 0 : i[0];
	cx = ((float)ymur * (float)env->t[1].width);
	while(i[0] >= 0 && i[0] < env->l.r[1] && i[0] <= i[1])
	{
		cy = (i[0] - start) * ch;
		color = index_color( cx , cy, &(env->t[2]));
		my_put_pixel(&(env->i),env->nbray,i[0], color);	
		i[0]++;
	}
	return ;
}

void	drawcolW(struct	s_env *env, int *i, double x)
{
	double		ymur;
	double		ch;
	int		hmur;
	int		start;
	int		color;

	float	cx;
	float	cy;

	ymur = x - ((int)x);
	hmur = (i[1] - i[0]);
	cx = ((float)env->t[3].width) / ((float)hmur);
	ch = ((float)env->t[3].height) / ((float)hmur);
	start = i[0];
	i[0] = (i[0] < 0)? 0 : i[0];
	cx = ((float)ymur * (float)env->t[3].width);
	while(i[0] >= 0 && i[0] < env->l.r[1] && i[0] <= i[1])
	{
		cy = (i[0] - start) * ch;
		color = index_color( cx , cy, &(env->t[3]));
		my_put_pixel(&(env->i),env->nbray,i[0], color);	
		i[0]++;
	}
	return ;

}


void	drawcol2(struct s_env *env,int *i, int color, double x, double y)
{
	if(color == 1)
		drawcolN(env, i, y);
	if(color == 2)
		drawcolS(env, i, y);
	if(color == 3)
		drawcolE(env, i, x);
	if(color == 4 || color == 0)
		drawcolW(env, i, x);
	return ;
}

