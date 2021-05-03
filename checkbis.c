/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkbeforeopen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 12:48:04 by labintei          #+#    #+#             */
/*   Updated: 2021/04/30 18:12:19 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int		create_trtgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

void	my_put_pixel(struct	s_img	*i, int x, int y, int color)
{
	char	*dest;

	dest = i->addr + (y * i->line_lenght + x * (i->bits_per_pixels / 8));
	*(unsigned int*)dest = color;
	return ;
}


void	drawcarre(int	x, int y, int largeur, struct s_env *env, int color)
{
	int		a;
	int		b;

	if(x >= 0 && y >= 0 && (x + largeur) < env->l.r[0] && (y + largeur) < env->l.r[1])
	{
		a = -1;
		while(++a < largeur)
		{
			b = -1;
			while(++b < largeur)
				my_put_pixel(&(env->i), x + b, y + a, color);
		}
	}
	return;
}

void	print_background(struct s_env	*env)
{
	int		x;
	int		y;
	int		o;

	o = env->l.r[1]/2;
	y = -1;
	while(++y < o)
	{	x = -1;
		while(++x < env->l.r[0])
			my_put_pixel(&(env->i),x ,y,create_trtgb(0,env->l.c[0],env->l.c[1],env->l.c[2]));
	}
	--y;
	while(++y < env->l.r[1])
	{
		x = -1;
		while(++x < env->l.r[0])
			my_put_pixel(&(env->i), x, y, create_trtgb(0,env->l.f[0],env->l.f[1],env->l.f[2]));
	}
	return ;
}

