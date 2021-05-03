/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openmap7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 10:06:25 by labintei          #+#    #+#             */
/*   Updated: 2021/04/30 17:35:14 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int		ft_putstr_err(char *s)
{
	int		i;

	i = -1;
	while(s[++i] != '\0')
		write(1, &(s[i]), 1);
	return(1);
}

char	ft_find(char c,char *s)
{
	while(*s)
	{
		if(*s == c)
			return(c);
		s++;
	}
	return(0);
}

void	stockdir(char **s1,char *s)
{
	int		n;

	n = 0;
	if((s1))
	{
		while(s[n])
			n++;
		if(!(*s1 = malloc(sizeof(char) * (n + 1))))
			return ;
		n = -1;
		while(s[++n])
			(*s1)[n] = s[n];
		(*s1)[n] = '\0';
	}
	return ;
}

void	ft_map_cut(struct s_list *l, int j)
{
	int		t;
	int		i;
	int		v;
	int		min;
	int		max;
	int		stock;
	int		ligne;

	min = -1;
	max = 0;
	i = 0;
	t = 0;
	ligne = 1;
	while(l->stock[t] && t <= j)
	{
		if(l->stock[t] == '\n')
			ligne++;
		t++;
	}
	t = 0;
	while(l->stock[t] && t <= j)
	{
		i = 0;
		v = t;
		while(l->stock[t] && l->stock[t] == ' ' && l->stock[t] != '\n' && t <= j)
		{
			t++;
			i++;
		}
		i = (i < 0) ? 0 : i;
		stock = min;
		min = ((i < min) || min == -1) ? i  : stock;
		while(l->stock[t] && l->stock[t] != '\n' && t <= j)
			t++;
		if(l->stock[t] == '\n' && l->stock[t] && t <= j)
			t++;
	}
	t = 0;
	while(l->stock[t] && t <= j)
	{
		i = 0;
		while(ft_find(l->stock[t], " 012NSWOE") && l->stock[t] != '\n' && l->stock[t] && t <= j)
		{
			t++;
			i++;
		}
		max = (max > i) ? max : i;
		while(l->stock[t] != '\n' && l->stock[t] && t <= j)
			t++;
		if(l->stock[t] == '\n' && t <= j)
			t++;
	}
	ft_put_map(l, min, max, j, ligne);
	return ;
}


int		main(int	argc, char	**argv)
{
	char	*s;
	char	*sbis;
	int		i;
	int		j;
	static struct s_env  env;

	i = 0;
	s = "cub";
	sbis = "--save";
	if(argc == 3)
	{
		while(argv[2][(int)i] && argv[2][i] == sbis[i])
			i++;
		env.save = (argv[2][(int)i] == '\0')?1 : 0;
	}
	i = 0;
	while(((argv[1])[i]) != '.' && ((argv[1])[i]))
		i++;
	j = ++i;
	while((s[i - j]) == ((argv[1])[i]) && (s[i - j] && (argv[1][i])))
		i++;
	if(s[i - j] == argv[1][i] && s[i - j] == '\0')
	{
		env.l.n = 0;
		if((env.l.fd = open(argv[1], O_RDONLY)) < 0)
			return(ft_putstr_err("Error\n"));
		treat_map(&(env.l));
		if((check_map(&(env.l))))
			open_window(&env);
		return(ft_putstr_err("Error\n"));
	}
	return(ft_putstr_err("Error\n"));
}
