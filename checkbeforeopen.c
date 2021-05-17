/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkbeforeopen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 12:48:04 by labintei          #+#    #+#             */
/*   Updated: 2021/05/17 12:59:37 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	init_p(struct s_env *env)
{
	int		i[2];

	while (env->l.map[env->ymax][env->xmax] != '\0')
		(env->xmax)++;
	while (env->l.map[env->ymax] != 0)
		(env->ymax)++;
	i[0] = -1;
	while (++i[0] < env->ymax)
	{
		i[1] = -1;
		while (++i[1] < env->xmax)
		{
			if (ft_find(env->l.map[i[0]][i[1]], "NSWE"))
			{
				env->play.x = i[1] + 0.5;
				env->play.y = i[0] + 0.5;
				env->play.pa = 0;
				init_angle(env, i);
			}
		}
	}
	env->pas = (env->l.r[0] / env->xmax) / 2;
	if (env->l.r[1] / env->ymax < (env->l.r[0] / env->xmax))
		env->pas = (env->l.r[1] / env->ymax) / 2;
}

void	draw_minimap(struct s_env *env)
{
	int		x;
	int		y;

	env->c = create_trtgb(0, 150, 180, 201);
	y = -1;
	while (env->l.map[++y])
	{
		x = -1;
		while (env->l.map[y][++x])
		{
			if (env->l.map[y][x] == '1')
				env->c = create_trtgb(0, 150, 180, 201);
			if (env->l.map[y][x] == '2')
				env->c = create_trtgb(0, 250, 180, 121);
			if (env->l.map[y][x] == '0')
				env->c = create_trtgb(0, 21, 80, 50);
			drawcarre(x * env->pas, y * env->pas, env->pas, env);
		}
	}
	env->c = create_trtgb(0, 150, 150, 150);
	drawcarre(env->play.x * env->pas, env->play.y * env->pas, 10, env);
	return ;
}

char	check(void **k, struct s_list *l, struct s_params *i, char **s, int *r)
{
	(void)l;
	*k = mlx_xpm_file_to_image(i->mlx, *s, &(r[0]), &(r[1]));
	if (!(*k))
	{
		if(*k)
			mlx_destroy_image(i->mlx, *k);
		return (0);
	}
	if(*k)
		mlx_destroy_image(i->mlx, *k);
	return (1);
}

char	checkbe(struct s_list *l, struct s_params *i)
{
	int			r[2];
	void		*k;

	if (!(checkbe_bis(l, i, r)))
		return (0);
	if ((l->f[0] > 255 || l->f[1] > 255 || l->f[2] > 255) || \
	(l->f[0] > 255 || l->f[1] > 255 || l->f[2] > 255))
		return (0);
	if (!(check(&k, l, i, &(l->s), r)) || !(check(&k, l, i, &(l->no), r) || \
				!(check(&k, l, i, &(l->so), r)) || !(check(&k, l, i, &(l->ea), r)) \
				|| !(check(&k, l, i, &(l->we), r))))
		return (0);
	return (1);
}

int	f_key(struct s_env *env)
{
	double	i[4];

	init_spe(env, i);
	if (env->key[0])
	{
		if ((env->l.map[(int)(env->play.y - i[3])][(int)(env->play.x - i[2])] \
			) != '1')
		{
			env->play.x -= i[2];
			env->play.y -= i[3];
		}
	}
	if (env->key[2])
	{
		if (env->l.map[(int)(env->play.y + i[3])] \
		 [(int)(env->play.x + i[2])] != '1')
		{
			env->play.x += i[2];
			env->play.y += i[3];
		}
	}
	return (1);
}

int	open_window(struct s_env	*env)
{
	env->p.mlx = mlx_init();
	if (checkbe(&(env->l), &(env->p)))
	{
		if (env->save != 1)
			env->p.mlx_win = mlx_new_window(env->p.mlx, env->l.r[0], \
			env->l.r[1], "F");
		env->i.img = mlx_new_image(env->p.mlx, env->l.r[0], env->l.r[1]);
		env->i.addr = mlx_get_data_addr(env->i.img, &(env->i.bits_per_pixels), \
		&(env->i.line_lenght), &(env->i.endian));
		f_load_texture(env);
		stock_drawfov(env);
		dvarconst(env);
		t(env);
		if (env->save == 1)
			return (bmp_save_file(env));
		mlx_hook(env->p.mlx_win, 3, 1L << 1, key_release, env);
		mlx_hook(env->p.mlx_win, 2, 1L << 0, key_press, env);
		mlx_hook(env->p.mlx_win, 33, (1L << 17), destroy_ta_vie, env);
		mlx_hook(env->p.mlx_win, 12, 1L << 15, &t, env);
		mlx_loop_hook(env->p.mlx, print_background, env);
		mlx_put_image_to_window(env->p.mlx, env->p.mlx_win, env->i.img, 0, 0);
		mlx_loop(env->p.mlx);
		return (1);
	}
	return (1);
}
