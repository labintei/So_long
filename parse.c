/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 10:06:25 by labintei          #+#    #+#             */
/*   Updated: 2021/06/18 19:33:52 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_find(char c, char *s);

int	key_press(int keycode, struct s_env *env)
{
	if (keycode == KEY_A)
		env->key[0] = 1;
	else if (keycode == KEY_W)
		env->key[1] = 1;
	else if (keycode == KEY_D)
		env->key[2] = 1;
	else if (keycode == KEY_S)
		env->key[3] = 1;
	else if (keycode == KEY_ESC)
		env->key[4] = 1;
	return (0);
}

int	key_release(int keycode, struct s_env *env)
{
	if (keycode == KEY_A)
		env->key[0] = 0;
	else if (keycode == KEY_W)
		env->key[1] = 0;
	else if (keycode == KEY_D)
		env->key[2] = 0;
	else if (keycode == KEY_S)
		env->key[3] = 0;
	else if (keycode == KEY_ESC)
		env->key[4] = 0;
	return (0);
}

void	putsprite(struct s_env *env)
{
	return ;
}

int		destroy(struct s_env	*env)
{

	return(0);
}

void	my_put_pixel(struct s_img *i, int x, int y, int color)
{
	char	*dest;

	dest = i->addr + (y * i->line_lenght + x * (i->bits_per_pixels / 8));
	*(unsigned int *)dest = color;
	return ;
}

int	index_color(int x, int y, struct s_texture *text)
{
	int		index;

	index = (y * text->line_lenght + x * (text->bits_per_pixels / 8));
	return (((int *)text->addr)[index / 4]);
}

int	create_trtgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	drawcarre(int x, int y, int color, struct s_env *env)
{
	int		a;
	int		b;

	a = -1;
	while (++a < env->pas)
	{
		b = -1;
		while (++b < env->pas)
			if(x + b < env->x && x + b > 0 && y + a < env->y && y + a > 0)
				my_put_pixel(&(env->i), x + b, y + a, color);
	}
	return ;
}

void	print_player(struct s_env *env)
{

}

void	print_background(struct s_env *env)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while(++y < env->y)
	{
		x = -1;
		while(++x < env->x)
			my_put_pixel(&(env->i), x, y, env->color);
	}
}

void	print_wall(struct s_env *env)
{
	int		x;
	int		y;

	y = -1;
	while(env->map[++y])
	{
		x = -1;
		while(env->map[y][++x])
		{
			if(env->map[y][x] == '1')
				drawcarre(x * env->pas, y * env->pas, create_trtgb(0, 120, 130, 140), env);
			if(env->map[y][x] == 'E')
				drawcarre(x * env->pas, y * env->pas, create_trtgb(0, 150, 130, 110), env);
			if(env->map[y][x] == 'C')
				drawcarre(x * env->pas, y * env->pas, create_trtgb(0, 150, 130, 210), env);
		}
	}
}

void	player_exit(struct s_env *env)
{

}

void		f_key(struct s_env *env)
{
	if(env->key[0] == 1)
	{
		env->play.o = 0;
		if(env->map[(int)(env->play.y - 0.25)][env->play.x] != '1')
			env->play.y -= 0.25;
	}
	if(env->key[1] == 1)
	{
		env->play.o = 1;
		if(env->map[(int)(env->play.y - 0.25)][env->play.x] != '1')
			env->play.y -= 0.25;
	}
	if(env->key[2] == 1)
	{
		env->play.o = 2;
		if(env->map[env->play.y][(int)(env->play.x + 0.25)] != '1')
			env->play.x += 0.25;
	}
	if(env->key[3] == 1)
	{
		env->play.o = 3;
		if(env->map[(int)(env->play.y + 0.25)][env->play.x] != '1')
			env->play.y += 0.25;
	}
	if(env->map[(int)(env->play.y)][env->play.x] != 'C')
		env->map[env->play.y][env->play.x] = '0';
}

int		print_ecran(struct s_env	*env)
{
	f_key(env);
	print_background(env);
	print_wall(env);
	//print_player(env);
	return(0);
}

void	calcul_pas(struct s_env *env)
{
	float	pastock;
	float	pastock1;

	int		i;
	pastock = (float)env->y / (float)env->sizemapy;
	pastock1 = (float)env->x / (float)env->sizemapx;
	if(pastock1 < pastock)
		pastock = pastock1;
	env->pas = pastock - (pastock - (int)pastock);
}

void	afficher_map(struct s_env *env)
{
	mlx_get_screen_size(env->p.mlx, &env->x, &env->y);
	env->p.mlx = mlx_init();
	putsprite(env);
	env->color = create_trtgb(150, 190, 210, 120);
	env->p.mlx_win = mlx_new_window(env->p.mlx, env->x, env->y, "Window");
	env->i.img = mlx_new_image(env->p.mlx, env->x, env->y);
	env->i.addr = mlx_get_data_addr(env->i.img, &(env->i.bits_per_pixels), \
			&(env->i.line_lenght), &(env->i.endian));
	calcul_pas(env);
	mlx_hook(env->p.mlx_win, 3, 1L << 1, key_release, env);
	mlx_hook(env->p.mlx_win, 2, 1L << 0, key_press, env);
	mlx_hook(env->p.mlx_win, 33, (1L << 17), destroy, env);
	//mlx_hook(env->p.mlx_win, 12, 1L << 15, &t, env);
	mlx_loop_hook(env->p.mlx, print_ecran, env);
	mlx_put_image_to_window(env->p.mlx, env->p.mlx_win, env->i.img, 0, 0);
	mlx_loop(env->p.mlx);
}

void	posjoueur(struct s_env *env, int i, int j)
{
	env->play.y = 0.5 + i;
	env->play.x = 0.5 + j;
	env->play.o = 0;
}


int	checkmap(struct s_env *env)
{
	int	i;
	int	j;
	int p;
	int e;

	e = 0;
	p = 0;
	i = 0;
	j = 0;
	printf("\n");
	while(i < env->sizemapy)
	{
		j = 0;
		while(env->map[i][j])
		{
			if(ft_find(env->map[i][j], "0CPE"))
			{
				if(env->map[i][j] == 'P')
				{
					posjoueur(env, i, j);
					p += 1;
				}
				if(env->map[i][j] == 'E')
					e += 1;
				// CAS DES MAX A GERER
				if(i == 0 || j == 0)
					return(0);
				if(!ft_find(env->map[i - 1][j], "01CPE") \
					|| !ft_find(env->map[i + 1][j], "01CPE") \
					|| !ft_find(env->map[i][j - 1],"01CPE") ||\
					!ft_find(env->map[i][j + 1], "01CPE"))
					return(0);
			}
			write(1, &(env->map[i][j]), 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
	//printf("\n%d\n",p);
	if(p == 1 && e >= 1)
		return(1);
	else
		return(0);
}

int	ft_strlen(char *s)
{
	int		i;

	i = 0;
	while(*s)
	{
		s++;
		i++;
	}
	return(i);
}


int	ft_find(char c, char *s)
{
	while(*s)
	{
		if(c == *s)
			return(c);
		s++;
	}
	return(0);
}

int	parse_map(int fd, struct s_env *env)
{
	char **s;
	char *f;
	int			i;
	int			j;
	int			r;
	int max;

	i = 0;
	r = 0;
	i = 0;
	max = -1;
	s = malloc(sizeof(char *) * 1000);
	while(get_next_line(fd, &(s[i])) == 1)
	{
		printf("%s\n",s[i]);
		if(max == -1 || max < ft_strlen(s[i]))
			max = ft_strlen(s[i]);
		i++;
	}
	env->sizemapx = max;
	env->sizemapy = i;
	write(1, "\n", 1);
	env->map = malloc(sizeof(char *) * (env->sizemapy + 1));
	i = 0;
	while(i < env->sizemapy)
	{
		r = 0;
		env->map[i] = malloc(sizeof(char) * (max + 1));
		while(s[i][r])
		{
			env->map[i][r] = s[i][r];
			write(1, &(env->map[i][r]), 1);
			r++;
		}
		while(r < env->sizemapx)
		{
			env->map[i][r] = ' ';
			write(1, " ", 1);
			r++;
		}
		env->map[i][r] = '\0';
		write(1, "|", 1);
		write(1, "\n", 1);
		i++;
	}
	env->map[i] = NULL;
	return(1);
}

int	main(int argc, char **argv)
{
	t_env		env;

	if(argc != 2)
		return(2);
	env.fd = open(argv[1], O_RDONLY);
	if(env.fd < 0)
		return(2);
	if(!parse_map(env.fd, &env))
		return(2);
	//CLEAN
	if(!checkmap(&env))
	{
		printf("\nMAP IS KO");
		return(2);
	}
	afficher_map(&env);
	printf("\nMAP IS OK");
	return(1);
}
