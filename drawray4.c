/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawray4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 10:50:11 by labintei          #+#    #+#             */
/*   Updated: 2021/05/16 15:11:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void		couleur_r(double *r, double *i, struct s_env *env, char *c)
{
	if (c[1] == 2)
	{
		env->c = 1;
		if (i[2] > env->play.x)
			env->c = 0;
		r[1] = (h(env, i[2], i[3]));
		r[2] = i[2];
		r[3] = i[3];
	}
	else
	{
		env->c = 2;
		if (i[1] > env->play.y)
			env->c = 3;
		r[1] = (h(env, i[0], i[1]));
		r[2] = i[0];
		r[3] = i[1];
	}
}

void		checkboth_mur(struct s_env *env, char *c, double a, double *i)
{
	if (c[0] == 0)
	{
		i[0] += env->diff[2];
		i[1] += env->diff[3];
		if (!(i[0] > 0 && i[0] < env->xmax && i[1] > 0 && i[1] < env->ymax))
			c[0] = 1;
		else if (env->l.map[(int)i[1]][(int)i[0]] == '1')
			c[0] = 2;
	}
	if (c[1] == 0)
	{
		i[2] += env->diff[0];
		i[3] += env->diff[1];
		if (!(i[2] > 0 && i[2] < env->xmax && i[3] > 0 && i[3] < env->ymax))
			c[1] = 1;
		else if (env->l.map[(int)i[3]][(int)i[2]] == '1')
			c[1] = 2;
	}
	if (c[0] == 0 || c[1] == 0)
		checkboth_mur(env, c, a, i);
}

void		dray(struct s_env *env, double a)
{
	double	i[5];
	char	c[2];

	c[0] = 0;
	c[1] = 0;
	i[4] = a;
	if (a >= env->var[2])
		i[4] = a - env->var[2];
	if (i[4] < 0)
		i[4] += env->var[2];
	dvar(env, i[4]);
	init_i(env, i);
	if (!(i[0] > 0 && i[0] < env->xmax && i[1] > 0 &&\
	i[1] < env->ymax) || a == 0 || a == M_PI)
		c[0] = 1;
	else if (env->l.map[(int)i[1]][(int)i[0]] == '1')
		c[0] = 2;
	if (!(i[2] > 0 && i[2] < env->xmax && i[3] > 0 &&\
	i[3] < env->ymax) || a == env->var[3] || a == env->var[4])
		c[1] = 1;
	else if (env->l.map[(int)i[3]][(int)i[2]] == '1')
		c[1] = 2;
	if (c[0] == 0 || c[1] == 0)
		checkboth_mur(env, c, i[4], i);
	f_compare(env, i, c, a);
}

void		ft_number(struct s_list *l, char *s, int *i)
{
	int		z[5];

	z[4] = 0;
	if (s[*i] == 'R')
	{
		stock_number(s, i, &(l->r[z[4]]));
		z[4]++;
		stock_number(s, i, &(l->r[z[4]]));
	}
	if ((s[*i] == 'C' || s[*i] == 'F') && (s[*i]))
	{
		z[3] = (int)(s[*i]);
		z[4] = -1;
		while (s[*i] && ++z[4] <= 2)
			stock_number(s, i, &(z[z[4]]));
		z[4] = -1;
		while (++z[4] <= 2 && z[z[4]])
		{
			if ((char)z[3] == 'F')
				l->f[z[4]] = z[z[4]];
			else
				l->c[z[4]] = z[z[4]];
		}
	}
	l->n += 1;
}

char		check_map(struct s_list *l)
{
	int		i;
	int		j;
	char	u;

	u = 0;
	i = -1;
	while (l->map[++i])
	{
		j = -1;
		while (l->map[i][++j])
		{
			if (ft_find(l->map[i][j], "02NSWE"))
			{
				if (j == 0 || (!(l->map[i][j + 1])) || i == 0 || \
				!(l->map[i + 1]) || (!(ft_find(l->map[i][j + 1], "012NSWE"))) \
				|| (!(ft_find(l->map[i][j + 1], "012NSWE"))) || \
				(!(ft_find(l->map[i + 1][j], "012NSWE"))) || \
				(!(ft_find(l->map[i - 1][j], "012NSWE"))))
					return (0);
				u += (ft_find(l->map[i][j], "NSWE")) ? 1 : 0;
			}
		}
	}
	if (u > 1 || u == 0)
		return (0);
	return (1);
}
