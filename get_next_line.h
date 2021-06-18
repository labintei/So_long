/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 09:26:36 by labintei          #+#    #+#             */
/*   Updated: 2021/06/18 14:57:45 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct		s_list
{
	char			stock[100];
	int				fd;
	int				size;
}					t_list;

int					get_next_line_recur(t_list *l, char **line, int count);
int					get_next_line(int fd, char **line);
int					ftstrncpy(char *s, char *s2, int n);
int					ilyan(char *s, int n);
int					calculsize(t_list *l, char *buf, int *copy);

#endif
