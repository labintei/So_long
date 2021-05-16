/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 15:56:03 by user42            #+#    #+#             */
/*   Updated: 2021/05/16 23:39:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void		drawcol_sprite(struct s_env *env, int *i, double d)
{
	double	c[3];
	int		start;
	int		color;

	c[0] = d * env->t[4].width;
	c[1] = ((float)env->t[4].height) / (i[1] - i[0]);
	start = i[0];
	if (start < 0)
		start = 0;
	while (start >= 0 && start < env->l.r[1] && start <= i[1])
	{
		c[2] = (start - i[0]) * c[1];
		color = index_color(c[0], c[2], &(env->t[4]));
		if (color & 0x00FFFFF)
			my_put_pixel(&(env->i), env->nbray, start, color);
		start++;
	}
	return ;
}

void		drawcols(struct s_env *env, int *i, double y)
{
	int		start;
	int		color;
	double	c[3];

	c[1] = ((float)(env->t[env->c].height)) / ((i[1] - i[0]));
	start = i[0];
	if (i[0] < 0)
		i[0] = 0;
	c[0] = ((float)(y - ((int)y)) * env->t[env->c].width);
	while (i[0] >= 0 && i[0] < env->l.r[1] && i[0] <= i[1])
	{
		c[2] = (i[0] - start) * c[1];
		color = index_color(c[0], c[2], &(env->t[env->c]));
		my_put_pixel(&(env->i), env->nbray, i[0], color);
		i[0]++;
	}
	return ;
}

void		init_angle(struct s_env *env, int *i)
{
	env->play.pa = 0;
	if (env->l.map[i[0]][i[1]] == 'S')
		env->play.pa = M_PI / 2;
	if (env->l.map[i[0]][i[1]] == 'N')
		env->play.pa = 3 * M_PI / 2;
	if (env->l.map[i[0]][i[1]] == 'W')
		env->play.pa = M_PI;
	env->l.map[i[0]][i[1]] = '0';
}

char		checkbe_bis(struct s_list *l, struct s_params *i, int *r)
{
	if (l->r[0] <= 0 || l->r[1] <= 0 || l->f[0] < 0 || l->f[1] < 0 ||\
	l->f[2] < 0 || l->c[0] < 0 || l->c[1] < 0 || l->c[2] < 0 ||\
	l->c[0] > 255 || l->c[1] > 255 || l->c[2] > 255 || l->f[0] > 255 \
	|| l->f[1] > 255 || l->f[2] > 255)
		return (0);
	mlx_get_screen_size(i->mlx, &r[0], &r[1]);
	if (r[0] < l->r[0] || l->r[0] <= 0)
		l->r[0] = r[0];
	if (r[1] < l->r[1] || l->r[1] <= 0)
		l->r[1] = r[1];
	return (1);
}

void		stockdir(char **s1, char *s)
{
	int		n;

	n = 0;
	if ((s1))
	{
		while (s[n])
			n++;
		if (!(*s1 = malloc(sizeof(char) * (n + 1))))
			return ;
		n = -1;
		while (s[++n])
		{
			(*s1)[n] = s[n];
			s[n] = 0;
		}
		(*s1)[n] = '\0';
	}
	return ;
}
