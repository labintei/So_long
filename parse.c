/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 10:06:25 by labintei          #+#    #+#             */
/*   Updated: 2021/05/19 14:33:44 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	ft_map_cut(struct s_list *l, int j)
{
	int		y[5];

	y[0] = -1;
	y[1] = 0;
	y[2] = 1;
	y[3] = 0;
	y[4] = -1;
	while (l->stock[++y[4]] && y[4] <= j)
		if (l->stock[y[4]] == '\n')
			y[2]++;
	y[4] = -1;
	while (l->stock[y[4]] && y[4] <= j)
	{
		y[3] = 0;
		while (l->stock[++y[4]] && l->stock[y[4]] == ' ' && l->stock[y[4]] != \
				'\n' && y[4] <= j)
			y[3]++;
		if (y[3] < 0)
			y[3] = 0;
		if ((y[3] < y[0]) || y[0] == -1)
			y[0] = y[3];
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
		if (y[1] < y[3])
			y[1] = y[3];
		while (l->stock[y[4]] != '\n' && l->stock[y[4]] && y[4] <= j)
			y[4]++;
		if (l->stock[y[4]] == '\n' && y[4] <= j)
			y[4]++;
	}
	ft_put_map(l, y, j);
	return ;
}

int	main_bis(struct s_env *env, char **s)
{
	env->l.n = 0;
	env->l.fd = open(s[1], O_RDONLY);
	if (env->l.fd < 0)
		return (ft_putstr_err("Error fail to open the map\n"));
	if (treat_map(&(env->l)) == 0)
		return (ft_putstr_err("Error wrong configuration of the map\n"));
	if ((check_map(&(env->l))))
		open_window(env);
	return (ft_putstr_err("Error wrong configuration of the map\n"));
}

void	main_bis_bis(struct s_env *env, int *i, char **argv)
{
	char	*sbis;

	sbis = "--save";
	while (argv[2][(int)i[0]] && argv[2][i[0]] == sbis[i[0]])
		i[0]++;
	if (argv[2][(int)i[0]] == '\0')
	{
		env->save = 1;
		env->l.save = 1;
	}
	else
	{
		env->save = 0;
		env->l.save = 0;
	}
}

int	main(int argc, char **argv)
{
	char				*s;
	int					i[2];
	static struct s_env	env;

	i[0] = 0;
	s = "cub";
	if (argc == 3)
		main_bis_bis(&env, i, argv);
	if (argc <= 1)
		return (ft_putstr_err("Error not enough arguments\n"));
	i[0] = 0;
	while (((argv[1])[i[0]]) != '.' && ((argv[1])[i[0]]))
		i[0]++;
	i[1] = ++i[0];
	while ((s[i[0] - i[1]]) == ((argv[1])[i[0]]) && (s[i[0] - i[1]] && \
	(argv[1][i[0]])))
		i[0]++;
	if (s[i[0] - i[1]] == argv[1][i[0]] && s[i[0] - i[1]] == '\0')
		return (main_bis(&env, argv));
	return (ft_putstr_err("Error not follow by a .cub \n"));
}
