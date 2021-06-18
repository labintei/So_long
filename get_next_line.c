/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 09:51:59 by labintei          #+#    #+#             */
/*   Updated: 2021/06/18 15:08:47 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	calculsize(t_list *l, char *buf, int *copy)
{
	if (!l->size)
	{
		l->size = read(l->fd, l->stock, 100);
		if (l->size < 0)
			return (-1);
	}
	*copy = ftstrncpy(buf, l->stock, l->size);
	l->size = 0;
	return (1);
}

int	fonction_return(char **line, char *buf, int count, int (*i)[4])
{
	(*line) = malloc(sizeof(char) * (count + (*i)[1] + 1 + (*i)[0]));
	if (!(*line))
		return (-1);
	(*line)[count + (*i)[1]] = 0;
	if ((*i)[2] == 0)
		return (0);
	(*i)[2] -= ftstrncpy(*line + count, buf, (*i)[1]++) + 1;
	return (2);
}

int	get_next_line_recur(t_list *l, char **line, int count)
{
	char	buf[100];
	int		i[4];

	i[0] = 0;
	if (calculsize(l, buf, &(i[2])) == -1)
		return (-1);
	i[1] = ilyan(l->stock, i[2]);
	if (i[1] || i[2] == 0)
	{
		if (i[1] == 0)
			i[0] = 1;
		else
			i[1]--;
		i[3] = fonction_return(&(*line), buf, count, &i);
		if (i[3] != 2)
			return (i[3]);
		l->size = ftstrncpy(l->stock, buf + i[1], i[2]);
		return (1);
	}
	i[0] = get_next_line_recur(l, line, count + i[2]);
	ftstrncpy(*line + count, buf, i[2]);
	return (i[0]);
}

int	get_next_line(int fd, char **line)
{
	static struct s_list	l;

	if (fd < 0 || read(fd, *line, 0) < 0 || !line)
		return (-1);
	l.fd = fd;
	*line = NULL;
	return (get_next_line_recur(&l, line, 0));
}
