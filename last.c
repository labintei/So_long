/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 01:03:13 by user42            #+#    #+#             */
/*   Updated: 2021/05/08 21:39:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int		treat_map(struct s_list *l)
{
	int		i;
	int		j;
	char	s[10000];

	i = read(l->fd, s, 10000);
	if (!i || !(l->stock = malloc((sizeof(char)) * (++i))))
		return (0);
	i = -1;
	while (s[++i] && s[i] != '\0')
		(l->stock)[i] = s[i];
	(l->stock)[i] = '\0';
	j = i;
	i = 0;
	return (treat_map_1(l, &i, &j));
}

int		t(struct s_env *env)
{
	int		i[3];

	i[1] = -1;
	while (++i[1] < env->l.r[1] / 2)
	{
		i[2] = -1;
		while (++i[2] < env->l.r[0])
			my_put_pixel(&(env->i), i[2], i[1], create_trtgb(0, env->l.c[0], \
			env->l.c[1], env->l.c[2]));
	}
	--i[1];
	while (++i[1] < env->l.r[1])
	{
		i[2] = -1;
		while (++i[2] < env->l.r[0])
			my_put_pixel(&(env->i), i[2], i[1], \
			create_trtgb(0, env->l.f[0], env->l.f[1], env->l.f[2]));
	}
	drawfov_bis(env);
	draw_minimap(env);
	//mlx_put_image_to_window(env->p.mlx, env->p.mlx_win, env->i.img, 0, 0);
	return(1);
}
