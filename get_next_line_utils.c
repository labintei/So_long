/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 09:32:47 by labintei          #+#    #+#             */
/*   Updated: 2021/06/18 15:12:22 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ftstrncpy(char *dest, char *src, int n)
{
	int		i;

	i = -1;
	if (!src && !dest)
		return (0);
	while (++i < n)
		dest[i] = src[i];
	return (i);
}

int	ilyan(char *s, int n)
{
	int		i;

	i = -1;
	while (++i < n)
	{
		if (s[i] == '\n')
			return (i + 1);
	}
	return (0);
}
