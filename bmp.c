/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:40:24 by labintei          #+#    #+#             */
/*   Updated: 2021/04/29 15:25:33 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"map.h"

void		write_header(struct s_env *env, int fd)
{
	unsigned int	u[3];
	unsigned char	c[2];

	c[0] = 1;
	c[1] = 24;
	u[3] = 54;
	u[0] = (54) + ((env->l.r[0] * env->l.r[1]) * 4);
	u[2] = 40;
	u[1] = 54;
	write(fd, "BM", 2);
	write(fd, &u[0] ,4);
	write(fd, "\0\0\0\0", 4);
	write(fd, &u[1], 4);
	write(fd, &u[2], 4);
	write(fd, &(env->l.r[0]), 4);
	write(fd, &(env->l.r[1]), 4);
	write(fd, &(c[0]), 2);
	write(fd, &(c[1]), 2);
	write(fd, "\0\0\0\0" ,4);
	write(fd, &(u[3]), 4);
	write(fd, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 16);
	/* RECHECK LES DONNEES*/
	return ;
}

void		write_data(struct s_env *env, int fd)
{
	int		c[5];

	c[0] = env->l.r[1] - 1;
	while(c[0] >= 0)
	{
		c[1] = 0;
		while(c[1] < env->l.r[0])
		{
			c[2] = env->i.addr[c[0] * env->i.line_lenght + c[1] * env->i.bits_per_pixels / 8];
			c[3] = env->i.addr[c[0] * env->i.line_lenght + c[1] * env->i.bits_per_pixels / 8 + 1];
			c[4] = env->i.addr[c[0] * env->i.line_lenght + c[1] * env->i.bits_per_pixels / 8 + 2];
			write(fd, &c[2], 1);
			write(fd, &c[3], 1);
			write(fd, &c[4], 1);
			c[1]++;
		}
		c[0]--;
	}
}

void		bmp_save_file(struct s_env *env)
{
	int		fd;
	int		size;
	char	*file;

	fd = open("cube3d.bmp",O_CREAT ,S_IXOTH);
	if(!(file= (malloc((sizeof(char) * (size + 54))))))
		return (ft_putstr("Error \n"));
	write_header(env, fd);
	write_data(env, fd);
	free(file);
	close(fd);
	return ;
}

