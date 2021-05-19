/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 01:03:13 by user42            #+#    #+#             */
/*   Updated: 2021/05/19 14:32:45 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	treat_map(struct s_list *l)
{
	int		i;
	int		j;
	int		k;
	char	*s;

	s = "";
	l->stock = NULL;
	test(l->fd, &s, &(l->stock));
	if (!(l->stock))
		return (0);
	i = -1;
	k = 0;
	while (l->stock[k])
		k++;
	l->stock[k] = '\0';
	j = k;
	i = 0;
	return (treat_map_1(l, &i, &j));
}

int	t(struct s_env *env)
{
	int		i[3];

	f_key(env);
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
	return (1);
}

int	key_press(int keycode, struct s_env *env)
{
	if (keycode == KEY_A)
		env->key[0] = 1;
	else if (keycode == KEY_W)
		env->key[1] = 1;
	else if (keycode == KEY_D)
		env->key[2] = 1;
	else if (keycode == KEY_S)
		env->key[3] = 1;
	else if (keycode == KEY_RIGHT)
		env->key[4] = 1;
	else if (keycode == KEY_LEFT)
		env->key[5] = 1;
	else if (keycode == KEY_ESC)
		env->key[6] = 1;
	return (0);
}

int	key_release(int keycode, struct s_env *env)
{
	if (keycode == KEY_A)
		env->key[0] = 0;
	else if (keycode == KEY_W)
		env->key[1] = 0;
	else if (keycode == KEY_D)
		env->key[2] = 0;
	else if (keycode == KEY_S)
		env->key[3] = 0;
	else if (keycode == KEY_RIGHT)
		env->key[4] = 0;
	else if (keycode == KEY_LEFT)
		env->key[5] = 0;
	else if (keycode == KEY_ESC)
		env->key[6] = 0;
	return (0);
}
