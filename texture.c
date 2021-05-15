/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 15:56:03 by user42            #+#    #+#             */
/*   Updated: 2021/05/15 13:02:36 by labintei         ###   ########.fr       */
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
	start = (start < 0) ? 1 : start;
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
	i[0] = (i[0] < 0) ? 0 : i[0];
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
