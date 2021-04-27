/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkbeforeopen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 12:48:04 by labintei          #+#    #+#             */
/*   Updated: 2021/04/27 15:14:07 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

#define	KEY_A 97
#define	KEY_W 119
#define	KEY_D 100
#define	KEY_S 115
#define	KEY_ESC 65307
#define	KEY_RIGHT 65361
#define	KEY_LEFT 65363


int		create_trtgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

void	my_put_pixel(struct	s_img	*i, int x, int y, int color)
{
	char	*dest;

	dest = i->addr + (y * i->line_lenght + x * (i->bits_per_pixels / 8));
	*(unsigned int*)dest = color;
	return ;
}

void	drawdir_bis_1(struct s_env *env)
{
	double  x;
	double	y;
	char	c;

	c = 0;
	
	x = env->play.x * env->pas;
	y = env->play.y * env->pas;
	while(c == 0 && env->l.map[(int)(y/env->pas)] != 0 && env->l.map[(int)y/env->pas][(int)(x/env->pas)] != '\0')
	{
		if(x >= 0 && x < env->l.r[0] && y >= 0 && y < env->l.r[1])
		{
			if(env->l.map[(int)(y/env->pas)][(int)(x/env->pas)] != '1')
				my_put_pixel(&(env->i),x, y, create_trtgb(0,250,0,0));
			if(env->l.map[(int)(y/env->pas)][(int)(x/env->pas)] == '1')
				c++;
		}
		x += cos(env->play.pa + (M_PI/2));
		y += sin(env->play.pa + (M_PI/2));
	}
	return ;
}

void	drawdir(struct s_env *env)
{
	double  x;
	double	y;
	char	c;

	c = 0;
	
	x = env->play.x * env->pas;
	y = env->play.y * env->pas;
	while(c == 0 && env->l.map[(int)(y/env->pas)] != 0 && env->l.map[(int)y/env->pas][(int)(x/env->pas)] != '\0')
	{
		if(x >= 0 && x < env->l.r[0] && y >= 0 && y < env->l.r[1])
		{
			if(env->l.map[(int)(y/env->pas)][(int)(x/env->pas)] != '1')
				my_put_pixel(&(env->i),x, y, create_trtgb(0,250,250,250));
			if(env->l.map[(int)(y/env->pas)][(int)(x/env->pas)] == '1')
				c++;
		}
		x += cos(env->play.pa);
		y += sin(env->play.pa);
	}
	drawdir_bis_1(env);
	return ;
}

void	drawcarre(int	x, int y, int largeur, struct s_env *env, int color)
{
	int		a;
	int		b;

	if(x >= 0 && y >= 0 && (x + largeur) < env->l.r[0] && (y + largeur) < env->l.r[1])
	{
		a = -1;
		while(++a < largeur)
		{
			b = -1;
			while(++b < largeur)
				my_put_pixel(&(env->i), x + b, y + a, color);
		}
	}
	return;
}

void	print_background(struct s_env	*env)
{
	int		x;
	int		y;
	int		o;

	o = env->l.r[1]/2;
	y = -1;
	while(++y < o)
	{	x = -1;
		while(++x < env->l.r[0])
			my_put_pixel(&(env->i),x ,y,create_trtgb(0,env->l.c[0],env->l.c[1],env->l.c[2]));
	}
	--y;
	while(++y < env->l.r[1])
	{
		x = -1;
		while(++x < env->l.r[0])
			my_put_pixel(&(env->i), x, y, create_trtgb(0,env->l.f[0],env->l.f[1],env->l.f[2]));
	}
	return ;
}

void	ft_init_player(int x, int y, struct s_env *env)
{
	env->play.pa = 0;
	env->play.x = (double)x + 0.5;
	env->play.y = (double)y + 0.5;
	env->play.pa += (env->l.map[y][x] == 'N')? M_PI/2 : 0;
	env->play.pa += (env->l.map[y][x] == 'S')? 3 * M_PI / 2 : 0;
	env->play.pa += (env->l.map[y][x] == 'E')? 0 : 0;
	env->play.pa += (env->l.map[y][x] == 'W')? M_PI : 0;
	return ;
}

void	draw_minimap(struct	s_env *env,char o)
{
	int		maxX;
	int		x;
	int		y;
	int		color;
	x = -1;
	color = 0;
	maxX = -1;
	y = -1;
	while(env->l.map[++y])
	{
		x = -1;
		while(env->l.map[y][++x])
			maxX = (x > maxX) ? x : maxX;
	}
	y--;
	
	env->pas = env->l.r[1]/y;
	env->pas = (env->pas < (env->l.r[0]/maxX)) ? env->pas : (env->l.r[0]/maxX);
	y = -1;
	env->pas /= 2;
	while(env->l.map[++y])
	{	
		x = -1;
		while(env->l.map[y][++x])
		{
			if(o == 0 && (env->l.map[y][x] == 'N' || env->l.map[y][x] == 'W' || env->l.map[y][x] == 'S' || env->l.map[y][x] == 'E'))
				ft_init_player(x,y,env);
			color = (env->l.map[y][x] == '1')? create_trtgb(0,150,180,201) : color;
			color = (env->l.map[y][x] == '2')? create_trtgb(0,250,180,121) : color;
			color = (env->l.map[y][x] == '0')? create_trtgb(0,21,80,50) : color;
			drawcarre(x * env->pas, y * env->pas, env->pas, env, color);
		}
	}
	x = 0;
	y = env->pas;
	while(y < env->pas * 15)
	{
		x = env->pas - 1;
		while(++x < env->pas * 20)
			my_put_pixel(&(env->i), x, y, create_trtgb(0,250,250,250));
		y += env->pas;
	}
	x = env->pas;
	y = 0;
	while(x < env->pas * 20)
	{
		y = env->pas -1;
		while(++y < env->pas * 15)
			my_put_pixel(&(env->i), x, y, create_trtgb(0,250,250,250));
		x += env->pas;
	}
	return ;
}

char	checkimg(char *s, struct s_params *i)
{
	void	*k;
	int		g;
	int		j;

	if((!(k = mlx_xpm_file_to_image(i->mlx, s, &g, &j))))
	{
		ft_putstr("Error");
		return(1);
	}
	return(0);
}

char		checkbe(struct s_list *l, struct s_params *i)
{
	int			rlargeur;
	int			rhauteur;
	int			h;
	int			j;
	char		t;

	t = 0;
	j = 0;
	h = 0;
	mlx_get_screen_size(i->mlx, &rlargeur, &rhauteur);
	if(rlargeur < l->r[0] || l->r[0] < 0)
		l->r[0] = rlargeur;
	if(rhauteur < l->r[1] || l->r[1] < 0)
		l->r[1] = rhauteur;
	if(l->c[0] > 255 || l->c[1] > 255 || l->c[2] > 255)
		return(0);
	if(l->f[0] > 255 || l->f[1] > 255 || l->f[2] > 255)
		return(0);
	while(l->map[h])
	{
		j = 0;
		while(l->map[h][j])
		{
			t += (l->map[h][j] == 'N') ? 1 : 0;
			j++;
		}
		h++;
	}
	if(t != 1)
		return(0);
	if(checkimg((l->s), i) || checkimg((l->so), i) || checkimg((l->no), i) || checkimg((l->we), i) || checkimg((l->ea), i))
		return(0);
	return(1);
}

void		draw_player(struct s_env *env)
{
	drawcarre(env->play.x * env->pas, env->play.y * env->pas, 10, env , create_trtgb(0,180,180,180));
	drawdir(env);
	
	double  x;
	double	y;
	char	c;

	c = 0;
	
	x = env->play.x * env->pas;
	y = env->play.y * env->pas;


	while(c == 0 && env->l.map[(int)(y/env->pas)] != 0 && env->l.map[(int)y/env->pas][(int)(x/env->pas)] != '\0')
	{
		if(x >= 0 && x < env->l.r[0] && y >= 0 && y < env->l.r[1])
		{
			if(env->l.map[(int)(y/env->pas)][(int)(x/env->pas)] != '1')
				my_put_pixel(&(env->i),x, y, create_trtgb(0,250,250,250));
			if(env->l.map[(int)(y/env->pas)][(int)(x/env->pas)] == '1')
				c++;
		}
		x += cos(env->play.pa - (M_PI*2/360 * 45));
		y += sin(env->play.pa - (M_PI*2/360 * 45));
	}

	c = 0;
	
	x = env->play.x * env->pas;
	y = env->play.y * env->pas;

	while(c == 0 && env->l.map[(int)(y/env->pas)] != 0 && env->l.map[(int)y/env->pas][(int)(x/env->pas)] != '\0')
	{
		if(x >= 0 && x < env->l.r[0] && y >= 0 && y < env->l.r[1])
		{
			if(env->l.map[(int)(y/env->pas)][(int)(x/env->pas)] != '1')
				my_put_pixel(&(env->i),x, y, create_trtgb(0,0,250,250));
			if(env->l.map[(int)(y/env->pas)][(int)(x/env->pas)] == '1')
				c++;
		}
		x += cos(env->play.pa + (M_PI*2/360 * 45));
		y += sin(env->play.pa + (M_PI*2/360 * 45));
	}


	return ;
}

int			f_key(int	keycode, struct s_env	*env)
{
	double	j;
	double	px;
	double	py;
	double	rot;

	print_background(env);
	draw_minimap(env, 1);
	px = cos(env->play.pa) / 20;
	py = sin(env->play.pa) / 20;
	if(keycode == KEY_W)
		if(env->l.map[(int)(env->play.y + (1.2*py))][(int)(env->play.x + (1.2*px))] != '1')
		{
			env->play.x += px;
			env->play.y += py;
		}
	if(keycode == KEY_S)
		if(env->l.map[(int)(env->play.y - (1.2 *py))][(int)(env->play.x - (1.2* px))] != '1')
		{
			env->play.x -= px;
			env->play.y -= py;
		}
	j = M_PI/2;
	if(keycode == KEY_A)
		if(env->l.map[(int)(env->play.y + (sin(env->play.pa - j) / 20 + 0.001))]\
		[(int)(env->play.x + ((0.001 + cos(env->play.pa - j)) / 20))] != '1')
		{
			env->play.x += cos(env->play.pa - j) / 20;
			env->play.y += sin(env->play.pa - j) / 20;
		}
	if(keycode == KEY_D)
		if(env->l.map[(int)(env->play.y - 0.001 -((sin(env->play.pa - j)/20)))]\
		[(int)(env->play.x - 0.001 - (cos(env->play.pa - j)/20))] != '1')
		{
			env->play.x -= cos(env->play.pa - j)/20;
			env->play.y -= sin(env->play.pa - j)/20;
		}
	rot = (2 * M_PI) / 360;
	if(keycode == KEY_RIGHT)
	{
		env->play.pa -= rot * 1;
		env->play.pa += (env->play.pa < 0) ? 2 * M_PI : 0;
	}
	if(keycode == KEY_LEFT)
	{
		env->play.pa += rot * 1;
		env->play.pa -= (env->play.pa >= 2 * M_PI) ? 2 * M_PI : 0;
	}
	if(keycode == KEY_ESC)
		mlx_destroy_window(env->p.mlx, env->p.mlx_win);
	drawfov_bis(env);
	draw_player(env);
//	draw_minimap(env, 1);
//	draw_player(env);
	mlx_put_image_to_window(env->p.mlx, env->p.mlx_win, env->i.img, 0,0);
	mlx_loop(env->p.mlx);
	return(1);
}

void		open_windows2(struct s_env	*env)
{
	env->p.mlx_win = mlx_new_window(env->p.mlx, env->l.r[0], env->l.r[1], "Fenetre1");
	env->i.img = mlx_new_image(env->p.mlx, env->l.r[0], env->l.r[1]);
	env->i.addr = mlx_get_data_addr(env->i.img, &(env->i.bits_per_pixels), &(env->i.line_lenght), &(env->i.endian));
	f_load_texture(env);
	env->xmax = 0;
	env->ymax = 0;
	maxxy(env, &(env->xmax), &(env->ymax));
	stock_drawfov(env);
	dvarconst(env);
	print_background(env);
	draw_minimap(env, 0);
	drawfov_bis(env);
	draw_minimap(env, 0);
	draw_player(env);
	mlx_put_image_to_window(env->p.mlx, env->p.mlx_win, env->i.img, 0, 0);
	mlx_hook(env->p.mlx_win, 2, 1L<<0, f_key, env);
	mlx_loop(env->p.mlx);
	return ;
}

