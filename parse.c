/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 10:06:25 by labintei          #+#    #+#             */
/*   Updated: 2021/05/15 13:01:49 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	stockdir(char **s1, char *s)
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

void	ft_map_cut(struct s_list *l, int j)
{
	int		y[5];

	y[0] = -1;
	y[1] = 0;
	y[2] = 1;
	y[3] = 0;
	y[4] = -1;
	while (l->stock[++y[4]] && y[4] <= j)
		y[2] += (l->stock[y[4]] == '\n') ? 1 : 0;
	y[4] = -1;
	while (l->stock[y[4]] && y[4] <= j)
	{
		y[3] = 0;
		while (l->stock[++y[4]] && l->stock[y[4]] == ' ' && l->stock[y[4]]\
		!= '\n' && y[4] <= j)
			y[3]++;
		y[3] = (y[3] < 0) ? 0 : y[3];
		y[0] = ((y[3] < y[0]) || y[0] == -1) ? y[3] : y[0];
		while (l->stock[y[4]] && l->stock[y[4]] != '\n' && y[4] <= j)
			y[4]++;
	}
	ft_map_cut_2(l, y, j);
}

void	ft_map_cut_2(struct s_list *l, int *y, int j)
{
	y[4] = 0;
	while (l->stock[y[4]] && y[4] <= j)
	{
		y[3] = 0;
		while (ft_find(l->stock[y[4]], " 012NSWE") && l->stock[y[4]] != '\n' \
		&& l->stock[y[4]] && y[4] <= j)
		{
			y[4]++;
			y[3]++;
		}
		y[1] = (y[1] > y[3]) ? y[1] : y[3];
		while (l->stock[y[4]] != '\n' && l->stock[y[4]] && y[4] <= j)
			y[4]++;
		if (l->stock[y[4]] == '\n' && y[4] <= j)
			y[4]++;
	}
	ft_put_map(l, y, j);
	return ;
}

int		main_bis(struct s_env *env, char **s)
{
	env->l.n = 0;
	if ((env->l.fd = open(s[1], O_RDONLY)) < 0)
		return (ft_putstr_err("Error\n"));
	if (treat_map(&(env->l)) == 0)
		return (ft_putstr_err("Error\n"));
	if ((check_map(&(env->l))))
		open_window(env);
	return (ft_putstr_err("Error\n"));
}

int		main(int argc, char **argv)
{
	char				*s;
	char				*sbis;
	int					i[2];
	static struct s_env	env;

	i[0] = 0;
	s = "cub";
	sbis = "--save";
	if (argc == 3)
	{
		while (argv[2][(int)i[0]] && argv[2][i[0]] == sbis[i[0]])
			i[0]++;
		env.save = (argv[2][(int)i[0]] == '\0') ? 1 : 0;
	}
	if (argc == 1)
		return (ft_putstr_err("Error\n"));
	i[0] = 0;
	while (((argv[1])[i[0]]) != '.' && ((argv[1])[i[0]]))
		i[0]++;
	i[1] = ++i[0];
	while ((s[i[0] - i[1]]) == ((argv[1])[i[0]]) && (s[i[0] - i[1]] && \
	(argv[1][i[0]])))
		i[0]++;
	return ((s[i[0] - i[1]] == argv[1][i[0]] && s[i[0] - i[1]] == '\0') ?\
	(main_bis(&env, argv)) : (ft_putstr_err("Error\n")));
}
