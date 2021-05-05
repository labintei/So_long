/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openmap7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 10:06:25 by labintei          #+#    #+#             */
/*   Updated: 2021/05/05 23:55:53 by user42           ###   ########.fr       */
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
			i[1] = (ft_find(l->stock[i[0]], "012NSWE"))? 1 : i[1];
			i[0]++;
		}
		i[0] += (l->stock[i[0]] == '\n' && i[1] == 1)? 1 : 0;
	}
	i[0] -= (!(l->stock[i[0]]))? 1 : 0;
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
		while (l->stock[i[0]] && l->stock[i[0]] != '\n' && l->stock[i[0]] == ' ')
			i[0]++;
		i[1] = (l->stock[i[0]] != '\n')? 1 : i[1];
		if (l->stock[i[0]] == '\n')
		{
			l->stock += i[0] + 1;
			i[0] = 0;
		}
	}
	i[0] = 0;
	i[1] = -1;
	return(ft_map_define_2(l, i));
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
		i[1] += y[0] -1;
		i[2] = -1;
		while (l->stock[++i[1]] && ++i[2] <= (y[1] - y[0]) && l->stock[i[1]] != '\n' && i[1] <= j)
			l->map[i[0]][i[2]] = l->stock[i[1]];
		while (i[2] < (y[1] - y[0]))
		{
			l->map[i[0]][i[2]] = ' ';
			i[2]++;
		}
		if (i[2] == (y[1] - y[0]))
			l->map[i[0]][i[2]] = '\0';
		while ((l->stock[i[1]] != '\n' && l->stock[i[1]] && i[1] <= j))
			i[1]++;
		if(l->stock[i[1]] == '\n' && l->stock[i[1] + 1] && l->stock[i[1]])
			i[1]++;
		i[0]++;
	}
	(l->map)[y[2]] = 0;
}

void	treat_map(struct s_list *l)
{
	int		i;
	int		j;
	char	s[10000];

	if(!(i = read(l->fd, s, 10000)) || !(l->stock = malloc((sizeof(char)) * (++i))))
		return ;
	i = -1;
	while (s[++i] && s[i] != '\0')
		(l->stock)[i] = s[i];
	(l->stock)[i] = '\0';
	j = i;
	i = 0;
	while (l->stock[i] != '\0')
	{
		while (l->n < 8 && i < j && l->stock[i] != '\0')
		{
			while (i < j && (l->stock)[i] && !(ft_find((l->stock[i]), "RFCNSWE")))
				i++;
			if (i < j && (l->stock)[i] && ft_find(l->stock[i], "RFC"))
			{
				ft_putstr_err("1");
				ft_number(l, l->stock, &i);
			}
			if (i < j &&(l->stock)[i] && ft_find(l->stock[i], "NSWE"))
			{
				ft_putstr_err("2");
				ft_dir(l, l->stock, &i);
			}
			if(i >= j || l->stock[i] == '\0')
				return ;
			//else ++i;
		}
		if (l->n == 8 && i < j)
		{
			l->stock += i;
			ft_map_define(l);
			return ;
		}
		ft_putstr_err("7");
		return ;
	}
	ft_putstr_err("7");
}

void	stock_number(char *s, int *i, int *val)
{
	*val = 0;
	while ((!(ft_find(s[*i], "0123456789"))) && s[*i])
		(*i)++;
	(*i)--;
	while ((ft_find(s[++(*i)], "0123456789")) && (s[*i]))
		*val = (*val) * 10 + (s[*i] - '0');
}

void	ft_number(struct s_list *l, char *s, int *i)
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

char	check_map(struct s_list *l)
{
	int		i;
	int		j;
	char	u;

	u = 0;
	i = -1;
	while (l->map[++i] && l->map[i + 1])
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
	return ((u > 1 || u == 0) ? 0 : 1);
}
