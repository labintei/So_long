/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:40:24 by labintei          #+#    #+#             */
/*   Updated: 2021/05/06 12:33:44 by user42           ###   ########.fr       */
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

int			bmp_save_file(struct s_env *env)
{
	int		fd;
	int		u[5];

	if ((fd = open("cube3d.bmp", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | \
	S_IWUSR)) < 0)
		return (ft_putstr_err("Error\n"));
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
	return (1);
}

void		ft_dir(struct s_list *l, char *s, int *i)
{
	char	t[10000];
	char	c[2];
	int		n;

	c[0] = (s[*i]);
	c[1] = (s[*i + 1]) ? s[*i + 1] : 0;
	n = 0;
	while (ft_find(s[*i], " \tNSWOEA") && s[*i])
		(*i)++;
	while ((s[(*i)] != '\n') && ((s[*i] != ' ')) && (s[*i] != '\0') && (s[*i]))
	{
		t[n] = s[(*i)];
		n++;
		(*i)++;
	}
	t[n] = '\0';
	return (ft_dir_bis(l, c, t));
}

void		ft_dir_bis(struct s_list *l, char *c, char *t)
{
	l->n++;
	if (c[0] == 'N' && c[1] == 'O' && (!(l->no)))
		stockdir((&(l->no)), t);
	if (c[0] == 'S' && c[1] == 'O' && (!(l->so)))
		stockdir((&(l->so)), t);
	if (c[0] == 'S' && c[1] != 'O' && (!(l->s)))
		stockdir((&(l->s)), t);
	if (c[0] == 'W' && c[1] == 'E' && (!(l->we)))
		stockdir((&(l->we)), t);
	if (c[0] == 'E' && c[1] == 'A' && (!(l->ea)))
		stockdir((&(l->ea)), t);
	return ;
}
