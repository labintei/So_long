/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 10:06:25 by labintei          #+#    #+#             */
/*   Updated: 2021/05/04 15:54:10 by user42           ###   ########.fr       */
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

void	stockdir(struct s_list *l, char **s1, char *s)
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
			(*s1)[n] = s[n];
		(*s1)[n] = '\0';
	}
	l->n += 1;
	free(s);
	return ;
}

void	ft_map_cut(struct s_list *l, int j)
{
	int		y[6];

	y[0] = -1;
	y[1] = 0;
	y[2] = 1;
	y[3] = 0;
	y[4] = 0;
	while (l->stock[y[4]] && y[4] <= j)
	{
		if (l->stock[y[4]] == '\n')
			y[2]++;
		y[4]++;
	}
	y[4] = 0;
	while (l->stock[y[4]] && y[4] <= j)
	{
		y[3] = 0;
		while (l->stock[y[4]] && l->stock[y[4]] == ' ' && l->stock[y[4]] != '\n' && y[4] <= j)
		{
			y[4]++;
			y[4]++;
		}
		y[3] = (y[3] < 0) ? 0 : y[3];
		y[5] = y[0];
		y[0] = ((y[3] < y[0]) || y[0] == -1) ? y[3] : y[5];
		while (l->stock[y[4]] && l->stock[y[4]] != '\n' && y[4] <= j)
			y[4]++;
		if (l->stock[y[4]] == '\n' && l->stock[y[4]] && y[4] <= j)
			y[4]++;
	}
	y[4] = 0;
	while (l->stock[y[4]] && y[4] <= j)
	{
		y[3] = 0;
		while (ft_find(l->stock[y[4]], " 012NSWOE") && l->stock[y[4]] != '\n' && l->stock[y[4]] && y[4] <= j)
		{
			y[4]++;
			y[3]++;
		}
		y[1] = (y[1] > y[3]++) ? y[1] : y[3]++;
		while (l->stock[y[4]] != '\n' && l->stock[y[4]] && y[4] <= j)
			y[4]++;
		if (l->stock[y[4]] == '\n' && y[4] <= j)
			y[4]++;
	}
	ft_put_map(l, y, j);
	return ;
}

int		main(int argc, char **argv)
{
	char				*s;
	char				*sbis;
	int					i;
	int					j;
	static struct s_env	env;

	i = 0;
	s = "cub";
	sbis = "--save";
	if (argc == 3)
	{
		while (argv[2][(int)i] && argv[2][i] == sbis[i])
			i++;
		env.save = (argv[2][(int)i] == '\0') ? 1 : 0;
	}
	i = 0;
	while (((argv[1])[i]) != '.' && ((argv[1])[i]))
		i++;
	j = ++i;
	while ((s[i - j]) == ((argv[1])[i]) && (s[i - j] && (argv[1][i])))
		i++;
	if (s[i - j] == argv[1][i] && s[i - j] == '\0')
	{
		env.l.n = 0;
		if ((env.l.fd = open(argv[1], O_RDONLY)) < 0)
			return (ft_putstr_err("Error\n"));
		treat_map(&(env.l));
		if ((check_map(&(env.l))))
			open_window(&env);
		return (ft_putstr_err("Error\n"));
	}
	return (ft_putstr_err("Error\n"));
}
