/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openmap7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 10:06:25 by labintei          #+#    #+#             */
/*   Updated: 2021/05/16 15:15:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	ft_map_define_2(struct s_list *l, int *i)
{
	while (l->stock[i[0]] && (i[1] == 1 || i[1] == -1))
	{
		i[1] = 0;
		while (l->stock[i[0]] && l->stock[i[0]] != '\n')
		{
			if (ft_find(l->stock[i[0]], "012NSWE"))
				i[1] = 1;
			i[0]++;
		}
		if (l->stock[i[0]] == '\n' || i[1] == 1)
			i[0] += 1;
	}
	if (!(l->stock[i[0]]))
		i[0] -= 1;
	while (l->stock[i[0]] && (l->stock[i[0]] == '\n' || l->stock[i[0]] == ' '))
		i[0]--;
	ft_map_cut(l, i[0]);
}

void	ft_map_define(struct s_list *l)
{
	int		i[2];

	i[0] = 0;
	i[1] = 0;
	while (i[1] == 0)
	{
		while (l->stock[i[0]] && l->stock[i[0]] != '\n' &&\
		l->stock[i[0]] == ' ')
			i[0]++;
		if (l->stock[i[0]] != '\n')
			i[1] = 1;
		if (l->stock[i[0]] == '\n')
		{
			l->stock += i[0] + 1;
			i[0] = 0;
		}
	}
	i[0] = 0;
	i[1] = -1;
	return (ft_map_define_2(l, i));
}

void	ft_put_map_1(struct s_list *l, int *y, int j, int *i)
{
	while (i[2] < (y[1] - y[0]))
	{
		l->map[i[0]][i[2]] = ' ';
		i[2]++;
	}
	if (i[2] == (y[1] - y[0]))
		l->map[i[0]][i[2]] = '\0';
	while ((l->stock[i[1]] != '\n' && l->stock[i[1]] && i[1] <= j))
		i[1]++;
	if (l->stock[i[1]] == '\n' && l->stock[i[1] + 1] && l->stock[i[1]])
		i[1]++;
	i[0]++;
}

void	ft_put_map(struct s_list *l, int *y, int j)
{
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if (!(l->map = malloc(sizeof(char *) * (y[2] + 1))))
		return ;
	while (l->stock[i[1]] && i[1] <= j && i[0] <= y[2])
	{
		if (!(((l->map)[i[0]]) = (malloc(sizeof(char) * ((y[1] - y[0]) + 1)))))
			return ;
		i[1] += y[0] - 1;
		i[2] = -1;
		while (l->stock[++i[1]] && ++i[2] <= (y[1] - y[0]) && l->stock[i[1]]\
		!= '\n' && i[1] <= j)
			l->map[i[0]][i[2]] = l->stock[i[1]];
		ft_put_map_1(l, y, j, i);
	}
	(l->map)[y[2]] = 0;
}

int		treat_map_1(struct s_list *l, int *i, int *j)
{
	while (l->stock[*i] != '\0')
	{
		while (l->n < 8 && *i < *j && l->stock[*i] != '\0')
		{
			while (*i < *j && !(ft_find((l->stock[*i]), "RFCNSWE")))
				(*i)++;
			if (*i < *j && (l->stock)[*i] && ft_find(l->stock[*i], "RFC"))
				ft_number(l, l->stock, i);
			if (i < j && (l->stock)[*i] && ft_find(l->stock[*i], "NSWE"))
				ft_dir(l, l->stock, i);
			if (*i >= *j || l->stock[*i] == '\0')
				return (0);
		}
		if (l->n == 8 && *i < *j)
		{
			l->stock += *i;
			ft_map_define(l);
			return (1);
		}
		return (0);
	}
	return (0);
}
