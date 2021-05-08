/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkbis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 12:48:04 by labintei          #+#    #+#             */
/*   Updated: 2021/05/08 21:47:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void		stock_number(char *s, int *i, int *val)
{
	*val = 0;
	while ((!(ft_find(s[*i], "0123456789"))) && s[*i])
		(*i)++;
	(*i)--;
	while ((ft_find(s[++(*i)], "0123456789")) && (s[*i]))
		*val = (*val) * 10 + (s[*i] - '0');
}

char		ft_find(char c, char *s)
{
	while (*s)
	{
		if (*s == c)
			return (c);
		s++;
	}
	return (0);
}

double		h(struct s_env *env, double x, double y)
{
	return (sqrt(pow(x - env->play.x, 2) + pow(y - env->play.y, 2)));
}

void		drawcarre(int x, int y, int largeur, struct s_env *env)
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

int			print_background(struct s_env	*env)
{
	mlx_hook(env->p.mlx_win, 33, (1L << 17), destroy_ta_vie, env);
	mlx_hook(env->p.mlx_win, 2, 1L << 0, f_key, env);
	t(env);
	mlx_put_image_to_window(env->p.mlx, env->p.mlx_win, env->i.img, 0, 0);
	//mlx_hook(env->p.mlx_win, 12, 1L << 15, &print_background, env);
	return (1);
}
