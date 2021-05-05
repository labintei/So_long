/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkbis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 12:48:04 by labintei          #+#    #+#             */
/*   Updated: 2021/05/05 17:40:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

char	ft_find(char c, char *s)
{
	while (*s)
	{
		if (*s == c)
			return (c);
		s++;
	}
	return (0);
}

double		cald(struct s_env *env, double x, double y)
{
	return (sqrt(pow(x - env->play.x, 2) + pow(y - env->play.y, 2)));
}

void	drawcarre(int x, int y, int largeur, struct s_env *env)
{
	int		a;
	int		b;

	if (x >= 0 && y >= 0 && (x + largeur) < env->l.r[0] && (y + largeur) <\
	env->l.r[1])
	{
		a = -1;
		while (++a < largeur)
		{
			b = -1;
			while (++b < largeur)
				my_put_pixel(&(env->i), x + b, y + a, env->c);
		}
	}
	return ;
}

void	print_background(struct s_env	*env)
{
	int		x;
	int		y;
	int		o;

	o = env->l.r[1] / 2;
	y = -1;
	while (++y < o)
	{
		x = -1;
		while (++x < env->l.r[0])
			my_put_pixel(&(env->i), x, y, create_trtgb(0, env->l.c[0], \
			env->l.c[1], env->l.c[2]));
	}
	--y;
	while (++y < env->l.r[1])
	{
		x = -1;
		while (++x < env->l.r[0])
			my_put_pixel(&(env->i), x, y, \
			create_trtgb(0, env->l.f[0], env->l.f[1], env->l.f[2]));
	}
	drawfov_bis(env);
	draw_minimap(env);
}
