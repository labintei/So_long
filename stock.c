/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 17:01:22 by user42            #+#    #+#             */
/*   Updated: 2021/05/19 14:35:41 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	init_p(struct s_env *env)
{
	int		i[2];

	while (env->l.map[env->ymax][env->xmax] != '\0')
		(env->xmax)++;
	while (env->l.map[env->ymax] != 0)
		(env->ymax)++;
	i[0] = -1;
	while (++i[0] < env->ymax)
	{
		i[1] = -1;
		while (++i[1] < env->xmax)
		{
			if (ft_find(env->l.map[i[0]][i[1]], "NSWE"))
			{
				env->play.x = i[1] + 0.5;
				env->play.y = i[0] + 0.5;
				env->play.pa = 0;
				init_angle(env, i);
			}
		}
	}
	env->pas = (env->l.r[0] / env->xmax) / 2;
	if (env->l.r[1] / env->ymax < (env->l.r[0] / env->xmax))
		env->pas = (env->l.r[1] / env->ymax) / 2;
}

void	libere_s(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		s[i] = 0;
		i++;
	}
	if (s)
		free(s);
	return ;
}

int	ft_strlen(char *s)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_join(char *s1, char *s2, int v)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] && (j < v || v == -1))
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	return (new);
}

void	test(int fd, char **s, char **new)
{
	char	*stock;
	char	*y;
	int		i;

	stock = malloc(sizeof(char) * 11);
	i = read(fd, stock, 10);
	stock[10] = '\0';
	if (i < 10)
	{
		*new = ft_join(*s, stock, i);
		libere_s(stock);
		return ;
	}
	else
	{
		y = ft_join(*s, stock, -1);
		test(fd, &y, new);
		i = 0;
		libere_s(y);
		libere_s(stock);
	}
	return ;
}
