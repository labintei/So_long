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

#include "map.h"

void		destroy_ta_vie(struct s_env		*env)
{
	mlx_destroy_image(env->p.mlx, env->t[0].img);
	mlx_destroy_image(env->p.mlx, env->t[1].img);
	mlx_destroy_image(env->p.mlx, env->t[2].img);
	mlx_destroy_image(env->p.mlx, env->t[3].img);
	mlx_destroy_image(env->p.mlx, env->t[4].img);
	if (env->save != 1)
		mlx_destroy_window(env->p.mlx, env->p.mlx_win);
	exit(0);
	return ;
}

void		init_envi(struct s_env	*env, double a)
{
	env->sp[0] = cos(a);
	env->sp[1] = sin(a);
	env->sp[2] = cos(env->play.pa + M_PI / 2);
	env->sp[3] = sin(env->play.pa + M_PI / 2);
	env->envi[1] = (a > M_PI) ? ((int)env->play.y) - 0.00001 : \
	((int)env->play.y) + 1;
	env->envi[0] = (a != 0 && a != M_PI) ? (env->play.x - \
	((env->play.y - env->envi[1]) / env->sp[1] * env->sp[0])) : 0;
	env->envi[2] = (a > env->var[4] && a < env->var[3]) ? \
	((int)env->play.x) - 0.00001 : ((int)env->play.x) + 1;
	env->envi[3] = (a != env->var[3] && a != env->var[4]) ?\
	env->play.y - ((env->play.x - env->envi[2]) / env->sp[0]) * env->sp[1] : 0;
	return ;
}

void		write_header(struct s_env *env, int fd, int *u)
{
	write(fd, &env->l.r[0], 4);
	write(fd, &env->l.r[1], 4);
	write(fd, &u[4], 2);
	write(fd, &env->i.bits_per_pixels, 2);
	write(fd, "\0\0\0\0", 4);
	write(fd, &u[3], 4);
	write(fd, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 16);
	u[0] = env->l.r[1];
	while (--u[0] >= 0)
	{
		u[1] = -1;
		while (++u[1] < env->l.r[0])
		{
			u[2] = env->i.addr[u[0] * env->i.line_lenght + u[1] * \
			env->i.bits_per_pixels / 8];
			u[3] = env->i.addr[u[0] * env->i.line_lenght + u[1] * \
			env->i.bits_per_pixels / 8 + 1];
			u[4] = env->i.addr[u[0] * env->i.line_lenght + u[1] * \
			env->i.bits_per_pixels / 8 + 2];
			write(fd, &u[2], 1);
			write(fd, &u[3], 1);
			write(fd, &u[4], 1);
			write(fd, "\0", 1);
		}
	}
}

int		bmp_save_file(struct s_env *env)
{
	int		fd;
	int	u[5];

	if ((fd = open("cube3d.bmp", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | \
	S_IWUSR)) < 0)
		return(ft_putstr_err("Error\n"));
	u[4] = 1;
	u[3] = (env->l.r[0] * env->l.r[1]);
	u[0] = (54) + ((env->l.r[0] * env->l.r[1]) * 4);
	u[2] = 40;
	u[1] = 54;
	write(fd, "BM", 2);
	write(fd, &u[0], 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, &u[1], 4);
	write(fd, &u[2], 4);
	write_header(env, fd, u);
	close(fd);
	destroy_ta_vie(env);
	return(1);
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
	n = -0;
	while(ft_find(s[*i]," \tNSWOEA") && s[*i])
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

