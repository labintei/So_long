/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkbeforeopen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 12:48:04 by labintei          #+#    #+#             */
/*   Updated: 2021/04/30 18:12:19 by labintei         ###   ########.fr       */
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

void	init_p(struct s_env *env)
{
	int		i;
	int		j;
	
	i= -1;
	while(++i < env->ymax)
	{
		j = -1;
		while(++j < env->xmax)
			if(ft_find(env->l.map[i][j],"NSWE"))
			{
				env->play.pa = 0;
				env->play.x = (double)j + 0.5;
				env->play.y = (double)i + 0.5;
				env->play.pa += (env->l.map[i][j] == 'N')? M_PI/2 : 0;
				env->play.pa += (env->l.map[i][j] == 'S')? 3 * M_PI / 2 : 0;
				env->play.pa += (env->l.map[i][j] == 'E')? 0 : 0;
				env->play.pa += (env->l.map[i][j] == 'W')? M_PI : 0;
			}
	}
	return ;
}

void	draw_minimap(struct	s_env *env)
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
			color = (env->l.map[y][x] == '1')? create_trtgb(0,150,180,201) : color;
			color = (env->l.map[y][x] == '2')? create_trtgb(0,250,180,121) : color;
			color = (env->l.map[y][x] == '0')? create_trtgb(0,21,80,50) : color;
			drawcarre(x * env->pas, y * env->pas, env->pas, env, color);
		}
	}
	drawcarre(env->play.x * env->pas, env->play.y * env->pas, 10, env , create_trtgb(0,180,180,180));
	return ;
}


char	checkimg(char *s, struct s_params *i)
{
	void	*k;
	int		g;
	int		j;

	if((!(k = mlx_xpm_file_to_image(i->mlx, s, &g, &j))))
	{
//		ft_putstr("Error");
		return(1);
	}
	mlx_destroy_image(i->mlx, k);
	return(0);
}
/*
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
}*/

char		checkbe(struct s_list *l, struct s_params *i)
{
	int			rlargeur;
	int			rhauteur;
	int			h;
	void		*k;

	h = 0;
	mlx_get_screen_size(i->mlx, &rlargeur, &rhauteur);
	if(rlargeur < l->r[0] || l->r[0] < 0)
		l->r[0] = rlargeur;
	if(rhauteur < l->r[1] || l->r[1] < 0)
		l->r[1] = rhauteur;
	rhauteur = 0;
	rlargeur = 0;
	if(l->c[0] > 255 || l->c[1] > 255 || l->c[2] > 255)
		return(0);
	if(l->f[0] > 255 || l->f[1] > 255 || l->f[2] > 255)
		return(0);
	if((!(k = mlx_xpm_file_to_image(i->mlx, l->s, &rhauteur, &rlargeur))))
		return(0);
	mlx_destroy_image(i->mlx, k);
	if((!(k = mlx_xpm_file_to_image(i->mlx, l->so, &rhauteur, &rlargeur))))
		return(0);
	mlx_destroy_image(i->mlx, k);
	if((!(k = mlx_xpm_file_to_image(i->mlx, l->we, &rhauteur, &rlargeur))))
		return(0);
	mlx_destroy_image(i->mlx, k);
	if((!(k = mlx_xpm_file_to_image(i->mlx, l->ea, &rhauteur, &rlargeur))))
		return(0);
	mlx_destroy_image(i->mlx, k);
	if((!(k = mlx_xpm_file_to_image(i->mlx, l->no, &rhauteur, &rlargeur))))
		return(0);
	mlx_destroy_image(i->mlx, k);
	return(1);
}

int			f_key(int	keycode, struct s_env	*env)
{
	double	j;
	double	px;
	double	py;
	double	rot;

	print_background(env);
	draw_minimap(env);
	px = cos(env->play.pa) / 20;
	py = sin(env->play.pa) / 20;
	if(keycode == KEY_W)
		if(env->l.map[(int)(env->play.y + py)][(int)(env->play.x + px)] != '1')
		{
			env->play.x += px;
			env->play.y += py;
		}
	if(keycode == KEY_S)
		if(env->l.map[(int)(env->play.y - py)][(int)(env->play.x - px)] != '1')
		{
			env->play.x -= px;
			env->play.y -= py;
		}
	j = M_PI/2;
	if(keycode == KEY_A)
		if(env->l.map[(int)(env->play.y + (sin(env->play.pa - j) / 20))]\
		[(int)(env->play.x + ((cos(env->play.pa - j)) / 20))] != '1')
		{
			env->play.x += cos(env->play.pa - j) / 20;
			env->play.y += sin(env->play.pa - j) / 20;
		}
	if(keycode == KEY_D)
		if(env->l.map[(int)(env->play.y - ((sin(env->play.pa - j)/20)))]\
		[(int)(env->play.x - (cos(env->play.pa - j)/20))] != '1')
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
	{
		destroy_ta_vie(env);
		return(1);
	}
	drawfov_bis(env);
	mlx_put_image_to_window(env->p.mlx, env->p.mlx_win, env->i.img, 0,0);
	mlx_loop(env->p.mlx);
	return(1);
}

int		open_window(struct s_env	*env)
{

	env->p.mlx = mlx_init();
	if(checkbe(&(env->l), &(env->p)))
	{
		if(env->save != 1)
			env->p.mlx_win = mlx_new_window(env->p.mlx, env->l.r[0], env->l.r[1],"F");
		env->i.img = mlx_new_image(env->p.mlx, env->l.r[0], env->l.r[1]);
		env->i.addr = mlx_get_data_addr(env->i.img, &(env->i.bits_per_pixels), &(env->i.line_lenght), &(env->i.endian));
		f_load_texture(env);
		maxxy(env);
		init_p(env);
		stock_drawfov(env);
		dvarconst(env);
		print_background(env);
		drawfov_bis(env);
		draw_minimap(env);
		if(env->save == 1)
			return(bmp_save_file(env));
		mlx_put_image_to_window(env->p.mlx, env->p.mlx_win, env->i.img, 0, 0);
		mlx_hook(env->p.mlx_win, 2, 1L<<0, f_key, env);
		mlx_loop(env->p.mlx);
		return(1);
	}
	return(ft_putstr_err("Error\n"));
}

