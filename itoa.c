/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:51:58 by labintei          #+#    #+#             */
/*   Updated: 2021/06/19 17:55:59 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int		size_int(int n)
{
	int		i;

	i = 1;
	while(n / 10)
	{
		n /= 10;
		i++;
	}
	return(i);
}

void	itoa(int n)
{
	char	*s;
	int		size;

	size = size_int(n);
	printf("%d\n", size);
	s = malloc(sizeof(char) * (size + 1));
	s[size] = '\0';
	while(--size >= 0)
	{
		s[size] = (n % 10) + '0';
		n /= 10;
	}
	printf("%s",s);
}


int	main(void)
{
	itoa(645645);
	printf("\n");
	itoa(654571);
	printf("\n");
	itoa(3);


}
