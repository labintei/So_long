/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 10:06:25 by labintei          #+#    #+#             */
/*   Updated: 2021/06/19 19:06:58 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_find(char c, char *s);

int	key_press(int keycode, struct s_env *env)
{
	env->play.action = 1;
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
	env->delay = 0;
	env->play.action = 0;
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

void	my_put_pixel(struct s_texture *i, int x, int y, int color)
{
	char	*dest;

	dest = i->addr + (y * i->line_lenght + x * (i->bits_per_pixels / 8));
	*(unsigned int *)dest = color;
	return ;
}

int	index_color(int x, int y, t_texture *text)
{
	int		index;

	index = (y * text->line_lenght + x * (text->bits_per_pixels / 8));
	return (((int *)text->addr)[index / 4]);
}

void set_pixel(t_texture *i, int x, int y, int color)
{
	*(unsigned int*)(i->addr + (y * i->line_lenght + x * (i->bits_per_pixels / 8))) = color;
}

int get_pixel(t_texture *img, int x, int y)
{
	return(*(int*)(img->addr + (y * img->line_lenght + (x * (img->bits_per_pixels / 8)))));
}

int	create_trtgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int		size_int(int n)
{
	int		i;

	i = 1;
	while(n / 10)
	{
		n /= 10;
		i++;
	}
	return(i);
}

void	ft_itoa(int n, char (*s)[10])
{
	int		size;

	size = size_int(n);
	(*s)[size] = '\0';
	while(--size >= 0)
	{
		(*s)[size] = (n % 10) + '0';
		n /= 10;
	}
//	return(s);
}



void	afficher_count(struct s_env *env)
{
	char	s[10];
	int		i[2];

	i[0] = env->i.width - (env->i.width / 30);
	i[1] = env->i.height - (env->i.height / 30);
	ft_itoa(env->count, &s);
	mlx_string_put(env->p.mlx, env->p.mlx_win, i[0], i[1], create_trtgb(0,0,0,0), s);
	//free(s);
}

typedef struct s_vector
{
	int		x;
	int		y;
}				t_vector;


void	drawcarre_texture_main(t_vector v, t_texture *text, struct s_env *env, int rev)
{
	int		a;
	int		b;
	unsigned int		color;

	a = -1;
	color = create_trtgb(250, 260, 150, 130);
	while (++a < env->pas)
	{
		b = -1;
		while (++b < env->pas)
		{	
			if(v.x + b < env->i.width && v.x + b > 0 && v.y + a < env->i.height && v.y + a > 0)
			{
				int rx = (int)(((float)b / (float)env->pas) * text->width);
				int ry = (int)(((float)a / (float)env->pas) * text->height);
				if (rev)
					rx = (text->width - 1) - rx;
				if(text->img)
					color = get_pixel(text, rx, ry);
				if(color != 0xFF000000)
					set_pixel(&(env->i), (v.x + b), (v.y + a), color);
			}
		}
	}
	return ;
}

void	drawcarre_texture(int x, int y, t_texture *text, struct s_env *env)
{
	t_vector pos;

	pos.x = x;
	pos.y = y;
	drawcarre_texture_main(pos, text, env, 0);
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
			if(x + b < env->i.width && x + b > 0 && y + a < env->i.height && y + a > 0)
				my_put_pixel(&(env->i), x + b, y + a, color);
	}
	return ;
}



void	draw_orientation(struct s_env *env, int i, int j, int h)
{
	t_vector pos;
	int rev;

	rev = 0;
	pos.x = (int)((env->play.x_s) * env->pas);
	pos.y = (int)((env->play.y_s) * env->pas);
	if (i == 0)
		rev = 1;
	if(env->play.action)
	{
		if(env->delay < 6)
			drawcarre_texture_main(pos, &(env->play.p[i]), env, rev);
		else
			drawcarre_texture_main(pos, &(env->play.p[j]), env, rev);
	}
	else
		drawcarre_texture_main(pos, &(env->play.p[h]), env, rev);
}


void	print_player(struct s_env *env)
{

	env->play.y_s -= (env->play.y_s - env->play.y) * 0.45;
	env->play.x_s -= (env->play.x_s - env->play.x) * 0.45;

	//drawcarre((int)((env->play.x_s) * env->pas), (int)((env->play.y_s) * env->pas), create_trtgb(0,150, 230, 150), env);
	if(env->play.o == 0)
		draw_orientation(env, 0, 1, 2);
	if(env->play.o == 1)
		draw_orientation(env, 3, 4, 5);
	if(env->play.o == 2)
		draw_orientation(env, 6, 7, 8);
	if(env->play.o == 3)
		draw_orientation(env, 9, 10, 11);
}

void	print_background(struct s_env *env)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while(++y < env->i.height)
	{
		x = -1;
		while(++x < env->i.width)
			my_put_pixel(&(env->i), x, y, env->color);
	}
}

void	print_collect(struct s_env *env, int x, int y)
{
	if(env->delay <= 3)
		drawcarre_texture(x * env->pas, y * env->pas, &(env->c.p[0]), env);
	else if(env->delay > 3 && env->delay <= 6)
		drawcarre_texture(x * env->pas, y * env->pas, &(env->c.p[1]), env);
	else if(env->delay >= 6 && env->delay < 8)
		drawcarre_texture(x * env->pas, y * env->pas, &(env->c.p[2]), env);
	else
		drawcarre_texture(x * env->pas, y * env->pas, &(env->c.p[3]), env);
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
			if(env->map[y][x] == '0' || env->map[y][x] == 'C')
				drawcarre_texture(x * env->pas, y * env->pas, &(env->f), env);
			if(env->map[y][x] == '1')
			{
				//drawcarre(x * env->pas, y * env->pas, create_trtgb(0, 120, 230, 140), env);
				drawcarre_texture(x * env->pas, y * env->pas, &(env->w), env);
			}
			if(env->map[y][x] == 'E')
				drawcarre(x * env->pas, y * env->pas, create_trtgb(0, 250, 130, 110), env);
			if(env->map[y][x] == 'C')
				print_collect(env, x, y);
			//	drawcarre(x * env->pas, y * env->pas, create_trtgb(0, 150, 130, 210), env);
		}
	}
}


int		f_key(struct s_env *env)
{
	int delay = 12;
	if (env->delay > 0)
		return (1);
	if(env->key[4] == 1)
		clear_all(env);
	if(env->key[0] == 1)
	{
		env->play.o = 0;
		if(env->map[env->play.y][(int)(env->play.x - 1)] != '1')
			env->play.x -= 1;
		env->delay = delay;
		env->count++;
	}
	if(env->key[1] == 1)
	{
		env->play.o = 1;
		if(env->map[(int)(env->play.y - 1)][env->play.x] != '1')
			env->play.y -= 1;
		env->delay = delay;
		env->count++;
	}
	if(env->key[2] == 1)
	{
		env->play.o = 2;
			if(env->map[env->play.y][(int)(env->play.x + 1)] != '1')
				env->play.x += 1;
		env->delay = delay;
		env->count++;
	}
	if(env->key[3] == 1)
	{
		env->play.o = 3;
		if(env->map[(int)(env->play.y + 1)][env->play.x] != '1')
			env->play.y += 1;
		env->delay = delay;
		env->count++;
	}
	if(env->map[env->play.y][env->play.x] == 'C')
		env->map[env->play.y][env->play.x] = '0';
	if(env->map[env->play.y][env->play.x] == 'E')
		clear_all(env);
	return(1);
}

int		print_ecran(struct s_env	*env)
{
	if (env->delay > 0)
		env->delay--;
	f_key(env);
	print_background(env);
	print_wall(env);
	print_player(env);
	mlx_put_image_to_window(env->p.mlx, env->p.mlx_win, env->i.img, 0, 0);
	afficher_count(env);

	return(0);
}

void	calcul_pas(struct s_env *env)
{
	float	pastock;
	float	pastock1;

	pastock = (float)env->i.height / ((float)env->sizemapy);
	pastock1 = (float)env->i.width / ((float)env->sizemapx);
	if(pastock1 < pastock)
		pastock = pastock1;
	env->pas = pastock - (pastock - (int)pastock);
}

void	afficher_map(struct s_env *env)
{
	env->p.mlx = mlx_init();
	env->delay = 0;
	env->count = 0;
	mlx_get_screen_size(env->p.mlx, &env->i.width, &env->i.height);
	env->i.width /= 2;
	env->i.height /= 2;
	//mlx_set_font(env->p.mlx, env->p.mlx_win, "Arial");
	f_load_texture(env);
	env->color = create_trtgb(150, 180, 170, 140);
	env->p.mlx_win = mlx_new_window(env->p.mlx, env->i.width, env->i.height, "Window");
	env->i.img = mlx_new_image(env->p.mlx, env->i.width, env->i.height);
	env->i.addr = mlx_get_data_addr(env->i.img, &(env->i.bits_per_pixels), \
			&(env->i.line_lenght), &(env->i.endian));
	calcul_pas(env);
	mlx_hook(env->p.mlx_win, 3, 1L << 1, key_release, env);
	mlx_hook(env->p.mlx_win, 2, 1L << 0, key_press, env);
	mlx_hook(env->p.mlx_win, 33, (1L << 17), clear_all, env);
	mlx_loop_hook(env->p.mlx, print_ecran, env);
	//mlx_hook(env->p.mlx_win, 12, 1L << 15, &t, env);
	mlx_put_image_to_window(env->p.mlx, env->p.mlx_win, env->i.img, 0, 0);
	mlx_loop(env->p.mlx);
}

void	posjoueur(struct s_env *env, int i, int j)
{
	env->play.y = 0.5 + i;
	env->play.x = 0.5 + j;
	env->play.y_s = env->play.y;
	env->play.x_s = env->play.x;
	env->play.o = 3;
	env->map[i][j] = '0';
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
	printf("\n%d\n",p);
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
	int			i;
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
