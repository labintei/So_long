/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:52:35 by labintei          #+#    #+#             */
/*   Updated: 2021/03/31 17:21:02 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx.h"
#include	<stdio.h>

typedef struct		s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
}					t_img;

typedef struct		s_params
{
	void	*mlx;
	void	*mlx_win;

}					t_params;

typedef struct		s_tex
{
	char	*f1;
	char	*f2;
	char	*f3;
	char	*f4;
	char	*f5;
	char	*f6;
	char	*f7;
	char	*f8;
}					t_tex;

typedef struct		s_texture
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
	int		width;
	int		height;
}					t_texture;

typedef struct		s_env
{
	t_params	p;
	t_img		i;
	t_tex		t;
	t_texture	ti[8];
}					t_env;


/*FONCTION POUR AFFICHER UNE IMAGE XPM*/

int			create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

void		my_put_pixel(struct s_img *i, int x, int y, int color)
{
	char	*dest;

	dest = i->addr + (y * i->line_lenght + x * (i->bits_per_pixel / 8));
	*(unsigned int*)dest = color;
	return ;
}

void		draw_rec(int x, int y, int largeur, int hauteur,struct s_img *i)
{
	int		a;
	int		b;

	a = 0;
	b = 0;
	if(x >= 0 && (x + largeur) <= 1980 && y >= 0 && (y + hauteur) <= 1220)
	{
		a = -1;
		while(++a < hauteur)
		{
			b = -1;
			while(++b < largeur)
				my_put_pixel(i, x + b, y + a, create_trgb(0,140,160,190));
		}
	}
	return ;
}

int			index_color(int x, int y,struct s_texture *txt)
{
	int		index;

	index = (y * txt->line_lenght + x * (txt->bits_per_pixel / 8));
	return(((int *)txt->addr)[index/4]);
}

void		drawtex(int	x, int	y, struct s_texture *t, struct s_img *i)
{
	int		color;
	int		a;
	int		b;

	a = -1;
	while(++a < 64)
	{
		b = -1;
		while(++b < 64)
		{
			color = index_color(a ,b,t);
			my_put_pixel(i, x + b , y + a , color);
		}
	}
	return	;
}

void		drawtex_size(int x, int y, int largeur,int hauteur,struct s_texture *t, struct s_img *i)
{
	float	rex;
	float	rey;


	int		color;
	int		a;
	int		b;

	(void)x;
	(void)y;
	(void)i;
	
	rex = (((float)t->height) / ((float)hauteur));
	rey = (((float)t->width) / ((float)largeur));
	printf("\n%f\n", rex);
	printf("\n%f\n", rey);
	a = -1;
	while(++a < hauteur)
	{
		b = -1;
		while(++b < largeur)
		{
			color = index_color((((int)(((float)a) * rex))),((int)(((float)b) * rey)), t);
			my_put_pixel(i, y + a, x + b, color);
		}
	}
	return ;
}


int			main(void)
{
	static struct s_env  env;
	env.t.f1 = "./sprite/1.xpm";
	env.t.f2 = "./sprite/2.xpm";
	env.t.f3 = "./sprite/4.xpm";
	env.t.f4 = "./sprite/5.xpm";
	env.t.f5 = "./sprite/6.xpm";
	env.t.f6 = "./sprite/mur.xpm";
	env.t.f7 = "./sprite/mur1.xpm";
	env.t.f8 = "./sprite/mur3.xpm";


	env.p.mlx = mlx_init();
	
	env.ti[0].img = mlx_xpm_file_to_image(env.p.mlx, env.t.f1 , &(env.ti[0].width), &(env.ti[0].height));
	env.ti[0].addr = mlx_get_data_addr(env.ti[0].img, &(env.ti[0].bits_per_pixel), &(env.ti[0].line_lenght), &(env.ti[0].endian));
	env.ti[1].img = mlx_xpm_file_to_image(env.p.mlx, env.t.f2 , &(env.ti[1].width), &(env.ti[1].height));
	env.ti[1].addr = mlx_get_data_addr(env.ti[1].img, &(env.ti[1].bits_per_pixel), &(env.ti[1].line_lenght), &(env.ti[1].endian));
	env.ti[2].img = mlx_xpm_file_to_image(env.p.mlx, env.t.f3 , &(env.ti[2].width), &(env.ti[2].height));
	env.ti[2].addr = mlx_get_data_addr(env.ti[2].img, &(env.ti[2].bits_per_pixel), &(env.ti[2].line_lenght), &(env.ti[2].endian));
	env.ti[3].img = mlx_xpm_file_to_image(env.p.mlx, env.t.f4 , &(env.ti[3].width), &(env.ti[3].height));
	env.ti[3].addr = mlx_get_data_addr(env.ti[3].img, &(env.ti[3].bits_per_pixel), &(env.ti[3].line_lenght), &(env.ti[3].endian));

	env.ti[4].img = mlx_xpm_file_to_image(env.p.mlx, env.t.f7 , &(env.ti[4].width), &(env.ti[4].height));
	env.ti[4].addr = mlx_get_data_addr(env.ti[4].img, &(env.ti[4].bits_per_pixel), &(env.ti[4].line_lenght), &(env.ti[4].endian));

	printf("\nheight%d\n",env.ti[4].height);
	printf("\nwidth%d\n",env.ti[4].width);

	env.p.mlx_win = mlx_new_window(env.p.mlx, 1980, 1220, "Fenetre 1");
	env.i.img = mlx_new_image(env.p.mlx, 1980,1220);
	env.i.addr = mlx_get_data_addr(env.i.img, &(env.i.bits_per_pixel), &(env.i.line_lenght), &(env.i.endian));
	draw_rec(0,0,1980,1220,&(env.i));
	drawtex(0,0, &(env.ti[0]), &(env.i));
	drawtex_size(250,250, 600, 800,&(env.ti[4]), &(env.i));
	mlx_put_image_to_window(env.p.mlx, env.p.mlx_win, env.i.img, 0, 0);
	mlx_loop(env.p.mlx);
}
