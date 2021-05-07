/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 15:44:26 by user42            #+#    #+#             */
/*   Updated: 2021/05/07 17:55:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int			create_trtgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void		my_put_pixel(struct s_img *i, int x, int y, int color)
{
	char	*dest;

	dest = i->addr + (y * i->line_lenght + x * (i->bits_per_pixels / 8));
	*(unsigned int*)dest = color;
	return ;
}

int			index_color(int x, int y, struct s_texture *text)
{
	int		index;

	index = (y * text->line_lenght + x * (text->bits_per_pixels / 8));
	return (((int *)text->addr)[index / 4]);
}

void		f_load_texture(struct s_env *env)
{
	env->t[0].img = mlx_xpm_file_to_image(env->p.mlx, env->l.no, \
	&(env->t[0].width), &(env->t[0].height));
	env->t[0].addr = mlx_get_data_addr(env->t[0].img, &(env->t[0].\
	bits_per_pixels), &(env->t[0].line_lenght), &(env->t[0].endian));
	env->t[1].img = mlx_xpm_file_to_image(env->p.mlx, env->l.so, \
	&(env->t[1].width), &(env->t[1].height));
	env->t[1].addr = mlx_get_data_addr(env->t[1].img, &(env->t[1].\
	bits_per_pixels), &(env->t[1].line_lenght), &(env->t[1].endian));
	env->t[2].img = mlx_xpm_file_to_image(env->p.mlx, env->l.we, \
	&(env->t[2].width), &(env->t[2].height));
	env->t[2].addr = mlx_get_data_addr(env->t[2].img, &(env->t[2].\
	bits_per_pixels), &(env->t[2].line_lenght), &(env->t[2].endian));
	env->t[3].img = mlx_xpm_file_to_image(env->p.mlx, env->l.ea, \
	&(env->t[3].width), &(env->t[3].height));
	env->t[3].addr = mlx_get_data_addr(env->t[3].img, &(env->t[3].\
	bits_per_pixels), &(env->t[3].line_lenght), &(env->t[3].endian));
	env->t[4].img = mlx_xpm_file_to_image(env->p.mlx, env->l.s, \
	&(env->t[4].width), &(env->t[4].height));
	env->t[4].addr = mlx_get_data_addr(env->t[4].img, &(env->t[4].\
	bits_per_pixels), &(env->t[4].line_lenght), &(env->t[4].endian));
	env->xmax = 0;
	env->ymax = 0;
	return ;
}

int			ft_putstr_err(char *s)
{
	int		i;

	i = -1;
	while (s[++i] != '\0')
		write(1, &(s[i]), 1);
	return (1);
}
