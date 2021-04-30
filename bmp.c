/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:40:24 by labintei          #+#    #+#             */
/*   Updated: 2021/04/30 18:12:40 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"map.h"

void		destroy_ta_vie(struct s_env		*env)
{
	mlx_destroy_image(env->p.mlx, env->t[0].img);
	mlx_destroy_image(env->p.mlx, env->t[1].img);
	mlx_destroy_image(env->p.mlx, env->t[2].img);
	mlx_destroy_image(env->p.mlx, env->t[3].img);
	mlx_destroy_image(env->p.mlx, env->t[4].img);
	if(env->save != 1)
		mlx_destroy_window(env->p.mlx, env->p.mlx_win);
	exit(0);
	return ;
}


void		init_envi(struct s_env	*env, double a)
{
	env->sp[0] = cos(a);
	env->sp[1] = sin(a);
	env->sp[2] = cos(env->play.pa + M_PI/2);
	env->sp[3] = sin(env->play.pa + M_PI/2);
	env->envi[1] = (a > M_PI)? ((int)env->play.y) - 0.00001 :\
	((int)env->play.y) + 1;
	env->envi[0] = (a != 0 && a != M_PI)? (env->play.x - \
	((env->play.y - env->envi[1])/env->sp[1] * env->sp[0])) : 0;
	env->envi[2] = (a > env->var[4] && a < env->var[3])? \
	((int)env->play.x) - 0.00001 : ((int)env->play.x) + 1;
	env->envi[3] = (a != env->var[3] && a != env->var[4])?\
	env->play.y - ((env->play.x - env->envi[2])/env->sp[0]) * env->sp[1] : 0;
	return ;
}

void		write_header(struct s_env *env, int fd)
{
	unsigned int	u[5];
	unsigned char	c[2];

	c[0] = 1;
	c[1] = 24;
	u[4] = env->l.r[0] * env->l.r[1];
	u[3] = 54;
	u[0] = (54) + ((env->l.r[0] * env->l.r[1]) * 4);
	u[2] = 40;
	u[1] = 54;
	write(fd, "BM", 2);
	write(fd, &u[0] ,4);
	write(fd, "\0\0\0\0", 4);
	write(fd, &u[1], 4);
	write(fd, &u[2], 4);
	write(fd, &env->l.r[0], 4);
	write(fd, &env->l.r[1], 4);
	write(fd, &(c[0]), 2);
	write(fd, &(env->i.bits_per_pixels), 2);
	write(fd, "\0\0\0\0" ,4);
	write(fd, &(u[4]), 4);
	write(fd, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 16);
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
	
	fd = open("cube3d.bmp",O_CREAT | O_RDWR);
	write_header(env, fd);
	write_data(env, fd);
	close(fd);
	destroy_ta_vie(env);
	return ;
}

