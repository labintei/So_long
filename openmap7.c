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

void	open_window(struct	s_env	*env)
{
	env->p.mlx = mlx_init();
	if(checkbe(&(env->l), &(env->p)))
	{
		open_windows2(env);
		return ;
	}
	else
		ft_putstr("Error");
	return;
}

void	ft_map_define(struct s_list *l)
{
	int		j;
	char	c;
	int		z;
	int		deb;
	int		end;

	deb = 0;
	end = 0;
	j = 0;
	c = 0;
	z = 0;
	while(c == 0)
	{
		while(l->stock[j] == ' ' && l->stock[j] != '\n' && l->stock[j])
			j++;
		if(l->stock[j] == '\n')
		{
			l->stock += j + 1;
			j = 0;
		}
		else 
			c = 1;
	}
	j = 0;
	z = -1;
	while(l->stock[j] && (z == 1 || z == -1))
	{
		z = 0;
		while(l->stock[j] && l->stock[j] != '\n')
		{
			if(ft_find(l->stock[j], "012N"))
				z = 1;
			j++;
		}
		if(l->stock[j] == '\n' && z == 1)
			j++;
	}
	if(!(l->stock[j]))
		j--;
	while(l->stock[j] && (l->stock[j]== ' ' || l->stock[j] == '\n'))
		j--;
	z = -1;
	ft_map_cut(l, j);
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
		while(ft_find(l->stock[t], " 012N") && l->stock[t] != '\n' && l->stock[t] && t <= j)
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

void	ft_put_map(struct s_list *l, int min, int max, int j, int ligne)
{
	int		t;
	int		i;
	int		o;

	i = 0;
	t = 0;
	o = 0;
	if(!(l->map = malloc(sizeof(char *) * (ligne + 1))))
		return ;
	while(l->stock[t] && t <= j && i <= ligne)
	{
		if(!(((l->map)[i]) = (malloc(sizeof(char) * ((max - min) + 1)))))
			return ;
		t += min;
		o = 0;
		while(l->stock[t] && o <= (max - min) && l->stock[t] != '\n' && t <= j)
		{
			l->map[i][o] = l->stock[t];
			o++;
			t++;
		}
		while(o < (max - min))
		{
			l->map[i][o] = ' ';
			o++;
		}
		if(o == (max - min))
			l->map[i][o] = '\0';
		while(l->stock[t] != '\n' && l->stock[t] && t <= j)
			t++;
		if(l->stock[t] == '\n' && l->stock[t + 1] && l->stock[t])
			t++;
		i++;
	}
	(l->map)[ligne] = 0;
	return ;
}

void	ft_putstr(char *s)
{
	int		i;

	i = -1;
	while(s[++i] != '\0')
		write(1, &(s[i]), 1);
	return ;
}

void	free_string(char *s)
{
	int		i;

	i = 0;
	while(s[i])
	{
		s[i] = 0;
		i++;
	}
	return ;
}


void	treat_map(struct s_list *l)
{
	int		n;
	int		i;
	char s[10000];

	i = -1;
	l ->stock = NULL;
	n = read(l->fd, s, 10000);
	l->stock = malloc((sizeof(char)) * (n + 1));
	while(s[++i] && s[i] != '\0')
		(l->stock)[i] = s[i];
	(l->stock)[i] = '\0';
	map(l);
	return ;
}

char	ft_find(char c, char *s)
{
	while(*s)
	{
		if(*s == c)
			return(c);
		s++;
	}
	return(0);
}

void	stockdir(char **s1, char *s)
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
	return;
}

void	ft_dir(struct s_list *l, char *s, int *i)
{
	char *t;
	char c;
	char y;
	int  n;
	int  b;

	t = NULL;
	t = malloc(sizeof(char) * 100);
	c = (s[*i]);
	y = (s[*i + 1]) ? s[*i + 1] : 0;
	n = 0;
	while(ft_find(s[*i]," \tNSWEOEA") && s[*i])
		(*i)++;
	while((s[(*i)] != '\n') && ((s[*i] != ' ')) && (s[*i] != '\0') && (s[*i]))
	{
		t[n] = s[(*i)];
		n++;
		(*i)++;
	}
	t[n] = '\0';
	b = 0;
	if(c == 'N' && (!(l->no)))
		stockdir((&(l->no)), t);
	if(c == 'S' && y == 'O' && (!(l->so)))
		stockdir((&(l->so)), t);
	if(c == 'S' && y != 'O'&& (!(l->s)))
		stockdir((&(l->s)), t);
	if(c == 'W' && (!(l->we)))
		stockdir((&(l->we)), t);
	if(c == 'E' && (!(l->ea)))
		stockdir((&(l->ea)), t);
	l->n += 1;
	free(t);
	return;
}

void	ft_number(struct s_list *l, char *s, int *i)
{
	int		n;
	int		t[2];
	int		z[3];
	char	y;

	n = 0;
	z[0] = 0;
	z[1] = 0;
	z[2] = 0;
	t[0] = 0;
	t[1] = 0;
	if(s[*i] == 'R' && (l->r[0] == -1) && (l->r[1] == -1))
	{
		while((!(ft_find(s[*i], "0123456789"))) && s[*i])
			(*i)++;
		(*i)--;
		while((ft_find(s[++(*i)], "0123456789")) && (s[*i]))
			t[n] = (t[n]) * 10 + (s[*i] - '0');
		while((!(ft_find(s[*i], "0123456789"))) && s[*i])
			(*i)++;
		(*i)--;
		n++;
		while((ft_find(s[++(*i)], "0123456789")) && (s[*i]))
			t[n] = (t[n]) * 10 + (s[*i] - '0');
		l->r[0] = t[0];
		l->r[1] = t[1];
		l->n += 1;
		return ;
	}
	if((s[*i] == 'C' || s[*i] == 'F') && (s[*i]))
	{
		y = (s[*i]);
		while(s[*i] && n <= 2)
		{
			while((!(ft_find(s[(*i)], "0123456789"))) && s[*i])
				(*i)++;
			(*i)--;
			while((ft_find(s[++(*i)], "0123456789")) && s[(*i)])
				z[n] = (z[n]) * 10 + (s[*i] - '0') + 0;
			n++;
		}
		n = 0;
		while(n <= 2 && z[n])
		{
			if(y == 'F')
				l->f[n] = z[n];
			else
				l->c[n] = z[n];
			n++;
		}
	}
	l->n += 1;
	return ;
}

void	map(struct s_list *l)
{
	int		i;

	i = 0;
	l->r[0] = -1;
	l->r[1] = -1;
	while(l->stock[i] != '\0')
	{
		while(l->n < 8)
		{
			while((l->stock)[i] && (!(ft_find((l->stock[i]), "RFCNSWE"))))
				i++;
			if((l->stock)[i] && ft_find(l->stock[i], "RFC"))
				ft_number(l, l->stock, &i);
			if((l->stock)[i] && ft_find(l->stock[i], "NSWE"))
				ft_dir(l, l->stock, &i);
		}
		if((l->stock[i] != '\0') && l->s && l->no && l->ea && l->we && l->so)
		{
			l->stock += i;
			ft_map_define(l);
			return ;
		}
	}
	return;
}

char	check_map(struct s_list *l)
{
	int		i;
	int		j;
	char	u;

	u = 0;
	j = 0;
	i = 0;
	while(l->map[i])
	{
		while(l->map[i][j])
		{
			if(ft_find(l->map[i][j],"02NSWE"))
			{
				if(j == 0 || (!(l->map[i][j + 1])))
					return(0);
				if(i == 0)
					return(0);
				if(!(l->map[i + 1]))
					return(0);
				if(ft_find(l->map[i][j],"NSWE"))
					u += 1;
				if((!(ft_find(l->map[i][j + 1],"012NSWE"))) || \
						(!(ft_find(l->map[i][j + 1], "012NSWE"))) || \
						(!(ft_find(l->map[i + 1][j], "012NSWE"))) || \
						(!(ft_find(l->map[i - 1][j], "012NSWE"))))
					return(0);
			}
			j++;
		}
		j = 0;
		i++;
	}
	if(u > 1 || u == 0)
		return(0);
	return(1);
}

void	openmap(char	*dir, char u)
{
	int		fd;
	static struct s_env  env;

	env.save = u;
	env.l.n = 0;
	fd = open(dir, O_RDONLY);
	env.l.fd = fd;
	treat_map(&(env.l));
	if((check_map(&(env.l))))
	{
		printf("OK");
		open_window(&env);
	}
	else
		ft_putstr("Error\n");
	return ;
}

int		main(int	argc, char	**argv)
{
	char	*s;
	char	*sbis;
	int		i;
	int		j;
	char	u;
	char	c;

	i = 0;
	u = 0;
	c = 0;
	s = "cub";
	sbis = "--save";
	if(argc == 3)
	{
		while(argv[2][(int)c] && argv[2][(int)c] == sbis[(int)c])
			c++;
		u = (argv[2][(int)c] == '\0')?1 : 0;
	}
	while(((argv[1])[i]) != '.' && ((argv[1])[i]))
		i++;
	j = ++i;
	while((s[i - j]) == ((argv[1])[i]) && (s[i - j] && (argv[1][i])))
		i++;
	if(s[i - j] == argv[1][i] && s[i - j] == '\0')
	{
		openmap(argv[1], u);
		return(1);
	}
	ft_putstr("Error\n");
	return(1);
}
