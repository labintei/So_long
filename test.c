/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 21:53:38 by labintei          #+#    #+#             */
/*   Updated: 2021/06/18 22:02:20 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

int test(int keycode, t_vars *vars)
{
	printf("Touche %d\n", keycode);
	(void)vars;
	return(0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello");
	mlx_key_hook(vars.win, test, &vars);
	mlx_loop(vars.mlx);
}

