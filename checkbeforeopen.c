/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkbeforeopen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 12:48:04 by labintei          #+#    #+#             */
/*   Updated: 2021/05/07 12:56:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

#define KEY_A 97
#define KEY_W 119
#define KEY_D 100
#define KEY_S 115

void		init_p(struct s_env *env)
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
			if (ft_find(env->l.map[i[0]][i[1]], "NSWE"))
			{
				env->play.x = i[1] + 0.5;
				env->play.y = i[0] + 0.5;
				env->play.pa = (env->l.map[i[0]][i[1]] == 'S') ? M_PI / 2 : 0;
				env->play.pa = (env->l.map[i[0]][i[1]] == 'N') ? 3 * M_PI / 2\
				: env->play.pa;
				env->play.pa = (env->l.map[i[0]][i[1]] == 'W') ? M_PI :\
				env->play.pa;
				env->l.map[i[0]][i[1]] = '0';
			}
	}
	env->pas = (env->l.r[1] / env->ymax < (env->l.r[0] / env->xmax)) ?\
	(env->l.r[1] / env->ymax) / 2 : (env->l.r[0] / env->xmax) / 2;
}

void		draw_minimap(struct s_env *env)
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
			env->c = (env->l.map[y][x] == '1') ? \
			create_trtgb(0, 150, 180, 201) : env->c;
			env->c = (env->l.map[y][x] == '2') ? \
			create_trtgb(0, 250, 180, 121) : env->c;
			env->c = (env->l.map[y][x] == '0') ? \
			create_trtgb(0, 21, 80, 50) : env->c;
			drawcarre(x * env->pas, y * env->pas, env->pas, env);
		}
	}
	env->c = create_trtgb(0, 150, 150, 150);
	drawcarre(env->play.x * env->pas, env->play.y * env->pas, 10, env);
	return ;
}

char		checkbe(struct s_list *l, struct s_params *i)
{
	int			r[2];
	void		*k;

	mlx_get_screen_size(i->mlx, &r[0], &r[1]);
	l->r[0] = (r[0] < l->r[0] || l->r[0] < 0) ? r[0] : l->r[0];
	l->r[1] = (r[1] < l->r[1] || l->r[1] < 0) ? r[1] : l->r[1];
	if ((l->f[0] > 255 || l->f[1] > 255 || l->f[2] > 255) || \
	(l->f[0] > 255 || l->f[1] > 255 || l->f[2] > 255) || \
	(!(k = mlx_xpm_file_to_image(i->mlx, l->s, &r[0], &r[1]))))
		return (0);
	mlx_destroy_image(i->mlx, k);
	if ((!(k = mlx_xpm_file_to_image(i->mlx, l->so, &r[0], &r[1]))))
		return (0);
	mlx_destroy_image(i->mlx, k);
	if ((!(k = mlx_xpm_file_to_image(i->mlx, l->we, &r[0], &r[1]))))
		return (0);
	mlx_destroy_image(i->mlx, k);
	if ((!(k = mlx_xpm_file_to_image(i->mlx, l->ea, &r[0], &r[1]))))
		return (0);
	mlx_destroy_image(i->mlx, k);
	if ((!(k = mlx_xpm_file_to_image(i->mlx, l->no, &r[0], &r[1]))))
		return (0);
	mlx_destroy_image(i->mlx, k);
	return (1);
}

int			f_key(int keycode, struct s_env *env)
{
	double	i[4];

	init_spe(env, keycode, i);
	if (keycode == KEY_A)
		if (env->l.map[(int)(env->play.y - i[3])]\
		[(int)(env->play.x - i[2])] != '1')
		{
			env->play.x -= i[2];
			env->play.y -= i[3];
		}
	if (keycode == KEY_D)
		if (env->l.map[(int)(env->play.y + i[3])]\
		[(int)(env->play.x + i[2])] != '1')
		{
			env->play.x += i[2];
			env->play.y += i[3];
		}
	print_background(env);
	mlx_put_image_to_window(env->p.mlx, env->p.mlx_win, env->i.img, 0, 0);
	mlx_loop(env->p.mlx);
	return (1);
}

int			open_window(struct s_env	*env)
{
	env->p.mlx = mlx_init();
	if (checkbe(&(env->l), &(env->p)))
	{
		if (env->save != 1)
			env->p.mlx_win = mlx_new_window(env->p.mlx, env->l.r[0],\
			env->l.r[1], "F");
		env->i.img = mlx_new_image(env->p.mlx, env->l.r[0], env->l.r[1]);
		env->i.addr = mlx_get_data_addr(env->i.img, &(env->i.bits_per_pixels),\
		&(env->i.line_lenght), &(env->i.endian));
		f_load_texture(env);
		env->xmax = 0;
		env->ymax = 0;
		init_p(env);
		stock_drawfov(env);
		dvarconst(env);
		print_background(env);
		if (env->save == 1)
			return (bmp_save_file(env));
		mlx_put_image_to_window(env->p.mlx, env->p.mlx_win, env->i.img, 0, 0);
		mlx_hook(env->p.mlx_win, 2, 1L << 0, f_key, env);
		mlx_loop(env->p.mlx);
		return (1);
	}
	return (1);
}
