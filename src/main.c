/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:55:25 by bnesoi            #+#    #+#             */
/*   Updated: 2019/06/21 12:52:38 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fractol.h"

int main(int argc, char **argv)
{
	t_app   app;
	void    *mlx;

	if (argc < 2 || argc > 3)
		ft_putendl(USAGE);
	else if (ft_strcmp(argv[1], HELP_ARG) == 0)
		ft_putendl(HELP);
	else
	{
		if (!(mlx = mlx_init()))
		{
			ft_putendl_fd("Failed to initialise mlx", 2);
			exit(1);
		}
		if (!app_start(&app, argv[1], mlx, argc == 3 ? argv[2] : NULL))
			app_finish(&app);
		else
		{
			mlx_loop(mlx);
			app_finish(&app);
		}
		free(mlx);
	}
	return (0);
}
