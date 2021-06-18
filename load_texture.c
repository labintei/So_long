/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 18:09:19 by labintei          #+#    #+#             */
/*   Updated: 2021/06/18 21:24:13 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	clear_all(struct s_env *env)
{
	mlx_destroy_image(env->p.mlx, env->play.p[0].img);
	mlx_destroy_image(env->p.mlx, env->play.p[1].img);
	mlx_destroy_image(env->p.mlx, env->play.p[2].img);
	mlx_destroy_image(env->p.mlx, env->play.p[3].img);
	mlx_destroy_image(env->p.mlx, env->play.p[4].img);
	mlx_destroy_image(env->p.mlx, env->play.p[5].img);
	mlx_destroy_image(env->p.mlx, env->play.p[6].img);
	mlx_destroy_image(env->p.mlx, env->play.p[7].img);
	mlx_destroy_image(env->p.mlx, env->play.p[8].img);
	mlx_destroy_image(env->p.mlx, env->c.p[0].img);
	mlx_destroy_image(env->p.mlx, env->c.p[1].img);
	mlx_destroy_image(env->p.mlx, env->c.p[2].img);
	mlx_destroy_image(env->p.mlx, env->c.p[3].img);
	mlx_destroy_image(env->p.mlx, env->w.img);
	mlx_destroy_image(env->p.mlx, env->e.img);
	mlx_destroy_image(env->p.mlx, env->i.img);
	mlx_destroy_window(env->p.mlx, env->p.mlx_win);
	mlx_destroy_display(env->p.mlx);
	exit(0);
}

void	f_load_colect(struct s_env *env)
{
	env->c.p[0].img = mlx_xpm_file_to_image(env->p.mlx, \
	"./sprite/collect/0.xpm",&(env->c.p[0].width), &(env->c.p[0].height));
	env->c.p[0].addr = mlx_get_data_addr(env->c.p[0].img,\
	&(env->c.p[0].bits_per_pixels), &(env->c.p[0].line_lenght),\
	&(env->c.p[0].endian));
	env->c.p[1].img = mlx_xpm_file_to_image(env->p.mlx, \
	"./sprite/collect/1.xpm",&(env->c.p[1].width), &(env->c.p[1].height));
	env->c.p[1].addr = mlx_get_data_addr(env->c.p[1].img,\
	&(env->c.p[1].bits_per_pixels), &(env->c.p[1].line_lenght),\
	&(env->c.p[1].endian));
	env->c.p[2].img = mlx_xpm_file_to_image(env->p.mlx, \
	"./sprite/collect/2.xpm",&(env->c.p[2].width), &(env->c.p[2].height));
	env->c.p[2].addr = mlx_get_data_addr(env->c.p[2].img, \
	&(env->c.p[2].bits_per_pixels), &(env->c.p[2].line_lenght),\
	&(env->c.p[2].endian));
	env->c.p[3].img = mlx_xpm_file_to_image(env->p.mlx, \
	"./sprite/collect/3.xpm",&(env->c.p[3].width), &(env->c.p[3].height));
	env->c.p[3].addr = mlx_get_data_addr(env->c.p[3].img, \
	&(env->c.p[3].bits_per_pixels), &(env->c.p[3].line_lenght),\
	&(env->c.p[3].endian));
}

void	f_load_player(struct s_env *env)
{
	env->play.p[0].img = mlx_xpm_file_to_image(env->p.mlx, \
	"./sprite/player/0.xpm",&(env->play.p[0].width), &(env->play.p[0].height));
	env->play.p[0].addr = mlx_get_data_addr(env->play.p[0].img, \
	&(env->play.p[0].bits_per_pixels), &(env->play.p[0].line_lenght), \
	&(env->play.p[0].endian));
	env->play.p[1].img = mlx_xpm_file_to_image(env->p.mlx, \
	"./sprite/player/1.xpm",&(env->play.p[1].width), &(env->play.p[1].height));
	env->play.p[1].addr = mlx_get_data_addr(env->play.p[1].img,\
	&(env->play.p[1].bits_per_pixels), &(env->play.p[1].line_lenght), \
	&(env->play.p[1].endian));
	env->play.p[2].img = mlx_xpm_file_to_image(env->p.mlx, \
	"./sprite/player/2.xpm",&(env->play.p[2].width), &(env->play.p[2].height));
	env->play.p[2].addr = mlx_get_data_addr(env->play.p[2].img,\
	&(env->play.p[2].bits_per_pixels), &(env->play.p[2].line_lenght),\
	&(env->play.p[2].endian));
	env->play.p[3].img = mlx_xpm_file_to_image(env->p.mlx, \
	"./sprite/player/3.xpm",&(env->play.p[3].width), &(env->play.p[3].height));
	env->play.p[3].addr = mlx_get_data_addr(env->play.p[3].img,\
	&(env->play.p[3].bits_per_pixels), &(env->play.p[3].line_lenght),\
	&(env->play.p[3].endian));
}

void	f_load_player_2(struct s_env *env)
{
	env->play.p[4].img = mlx_xpm_file_to_image(env->p.mlx, \
	"./sprite/player/4.xpm",&(env->play.p[4].width), &(env->play.p[4].height));
	env->play.p[4].addr = mlx_get_data_addr(env->play.p[4].img,\
	&(env->play.p[4].bits_per_pixels), &(env->play.p[4].line_lenght),\
	&(env->play.p[4].endian));
	env->play.p[5].img = mlx_xpm_file_to_image(env->p.mlx, \
	"./sprite/player/5.xpm",&(env->play.p[5].width), &(env->play.p[5].height));
	env->play.p[5].addr = mlx_get_data_addr(env->play.p[5].img, \
	&(env->play.p[5].bits_per_pixels), &(env->play.p[5].line_lenght), \
	&(env->play.p[5].endian));
	env->play.p[6].img = mlx_xpm_file_to_image(env->p.mlx, \
	"./sprite/player/6.xpm",&(env->play.p[6].width), &(env->play.p[6].height));
	env->play.p[6].addr = mlx_get_data_addr(env->play.p[6].img, \
	&(env->play.p[6].bits_per_pixels), &(env->play.p[6].line_lenght),\
	&(env->play.p[6].endian));
	env->play.p[7].img = mlx_xpm_file_to_image(env->p.mlx, \
	"./sprite/player/7.xpm",&(env->play.p[7].width), &(env->play.p[7].height));
	env->play.p[7].addr = mlx_get_data_addr(env->play.p[7].img, \
	&(env->play.p[7].bits_per_pixels), &(env->play.p[7].line_lenght), \
	&(env->play.p[7].endian));
	env->play.p[8].img = mlx_xpm_file_to_image(env->p.mlx, \
	"./sprite/player/8.xpm",&(env->play.p[8].width), &(env->play.p[8].height));
	env->play.p[8].addr = mlx_get_data_addr(env->play.p[8].img, \
	&(env->play.p[8].bits_per_pixels), &(env->play.p[8].line_lenght), \
	&(env->play.p[8].endian));
}

void	f_load_texture(struct s_env *env)
{
	f_load_colect(env);
	f_load_player(env);
	f_load_player(env);
	env->w.img = mlx_xpm_file_to_image(env->p.mlx, "./sprite/wall//0.xpm",\
	&(env->w.width), &(env->w.height));
	env->w.addr = mlx_get_data_addr(env->w.img, &(env->w.bits_per_pixels),\
	&(env->w.line_lenght), &(env->w.endian));
	env->e.img = mlx_xpm_file_to_image(env->p.mlx, "./sprite/exit//0.xpm",\
	&(env->e.width), &(env->e.height));
	env->e.addr = mlx_get_data_addr(env->e.img, &(env->e.bits_per_pixels),\
	&(env->e.line_lenght), &(env->e.endian));
}
