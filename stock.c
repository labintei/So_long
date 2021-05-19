/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 17:01:22 by user42            #+#    #+#             */
/*   Updated: 2021/05/19 10:44:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int		ft_strlen(char *s)
{
	int		i;

	i = 0;
	if(!s)
		return(0);
	while(s[i])
		i++;
	return(i);
}


char	*ft_join(char *s1, char *s2, int v)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	while(s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while(s2[j] && (j < v || v == -1))
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	return(new);
}


void	test(int fd, char **s, char **new)
{
	char	*stock;
	char	*y;
	int		i;

	stock = malloc(sizeof(char) * 10001);
	i = read(fd, stock, 10000);
	stock[10000] = '\0';
	if(i < 10000)
	{
		*new = ft_join(*s, stock, i);
		while(stock[i])
		{
			stock[i] = 0;
			i++;
		}
		free(stock);
		return ;
	}
	else
	{
		y = ft_join(*s, stock, -1);
		test(fd, &y, new);
		i = 0;
		while(y[i])
		{
			y[i] = 0;
			i++;
		}
		free(y);
		i = 0;
		while(stock[i])
		{
			stock[i] = 0;
			i++;
		}
		free(stock);
	}
	return ;
}


/*
char	 *test_stock(int	fd, char **line)
{
	char *stock;
	char *s;
	int		ret;
	int		i;

	stock = malloc(sizeof(char) * 10001);
	if((ret = read(fd, stock, 10000)) >= 10000)
		test_stock(fd, &s);
	stock = malloc(sizeof(char) * (ft_strlen(s) + ft_strlen(*line)));
	i = 0;
	while((*line)[i])
	{
		stock[i] = (*line)[i];
		i++;
	}
	ret = 0;
	while(s[ret])
	{
		stock[i + ret] = s[i];
		i++;
	}
	stock[i + ret] = '\0';
	return(stock);
}*/
/*
#include <stdio.h>

int		main(void)
{
	int		fd;
	char	*line;
	char	*new;
	int		i;

	i = 0;
	line = "";
	new = NULL;
	fd = open("test.txt", O_RDONLY);
	test(fd, &line, &new);
	printf("%s", new);
	i = 0;
	while(new[i])
	{
		new[i] = 0;
		i++;
	}
	free(new);
	i = 0;
	while(line[i])
	{
		line[i] = 0;
		i++;
	}
	return(1);
}*/
