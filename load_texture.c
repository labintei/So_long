/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 18:09:19 by labintei          #+#    #+#             */
/*   Updated: 2021/06/20 20:27:00 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	clear_image(struct s_env *env, struct s_texture text)
{
	if((text.img))
		mlx_destroy_image(env->p.mlx, (text.img));
}

int		clear_all(struct s_env *env)
{
	clear_image(env, env->play.p[0]);
	clear_image(env, env->play.p[1]);
	clear_image(env, env->play.p[2]);
	clear_image(env, env->play.p[3]);
	clear_image(env, env->play.p[4]);
	clear_image(env, env->play.p[5]);
	clear_image(env, env->play.p[6]);
	clear_image(env, env->play.p[7]);
	clear_image(env, env->play.p[8]);
	clear_image(env, env->c.p[0]);
	clear_image(env, env->c.p[1]);
	clear_image(env, env->c.p[2]);
	clear_image(env, env->c.p[3]);
	clear_image(env, env->w[0]);
	clear_image(env, env->w[1]);
	clear_image(env, env->w[2]);
	clear_image(env, env->w[3]);
	clear_image(env, env->e);
	clear_image(env, env->f);
	mlx_destroy_image(env->p.mlx, env->i.img);
	mlx_destroy_window(env->p.mlx, env->p.mlx_win);
	mlx_destroy_display(env->p.mlx);
	exit(0);
	return(0);
}

void	load(struct s_env *env, t_texture *img, char *path)
{
	img->img = mlx_xpm_file_to_image(env->p.mlx, \
	path ,&(img->width), &(img->height));
	if(img->img)
	{
		img->addr = mlx_get_data_addr(img->img,\
		&(img->bits_per_pixels), &(img->line_lenght),\
		&(img->endian));
	}
}

void	f_load_colect(struct s_env *env)
{
	load(env, &(env->c.p[0]), "./sprite/collect/14.xpm");
	load(env, &(env->c.p[1]), "./sprite/collect/15.xpm");
	load(env, &(env->c.p[2]), "./sprite/collect/16.xpm");
	load(env, &(env->c.p[3]), "./sprite/collect/15.xpm");
}

void	f_load_player(struct s_env *env)
{
	load(env, &(env->play.p[0]), "./sprite/player/7.xpm");
	load(env, &(env->play.p[1]), "./sprite/player/9.xpm");
	load(env, &(env->play.p[2]), "./sprite/player/8.xpm");
	load(env, &(env->play.p[3]), "./sprite/player/11.xpm");
	load(env, &(env->play.p[4]), "./sprite/player/12.xpm");
	load(env, &(env->play.p[5]), "./sprite/player/10.xpm");
	load(env, &(env->play.p[6]), "./sprite/player/7.xpm");
	load(env, &(env->play.p[7]), "./sprite/player/9.xpm");
	load(env, &(env->play.p[8]), "./sprite/player/8.xpm");
	load(env, &(env->play.p[9]), "./sprite/player/6.xpm");
	load(env, &(env->play.p[10]), "./sprite/player/4.xpm");
	load(env, &(env->play.p[11]), "./sprite/player/3.xpm");
}

void	f_load_wall(struct s_env *env)
{
	load(env, &(env->w[0]), "./sprite/wall/0.xpm");
	load(env, &(env->w[1]), "./sprite/wall/a1.xpm");
	load(env, &(env->w[2]), "./sprite/wall/a2.xpm");
	load(env, &(env->w[3]), "./sprite/wall/a3.xpm");
	load(env, &(env->w[4]), "./sprite/wall/a4.xpm");
}


void	f_load_texture(struct s_env *env)
{
	f_load_colect(env);
	f_load_player(env);
	f_load_wall(env);
	load(env, &(env->e), "./sprite/exit/10.xpm");
	load(env, &(env->f), "./sprite/floor/0.xpm");
}
