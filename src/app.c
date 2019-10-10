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

int app_render(t_app *app)
{
	app->ren.width = app->win_w;
	app->ren.height = app->win_h;
	if (!render(&app->ren, &app->ocl, app->pixel_ptr))
	{
		return (0);
	}
	mlx_put_image_to_window(app->mlx, app->win, app->img, 0, 0);
	return (1);
}

static int  app_loop(t_app *app)
{
	return (1);
}

static void app_connect_events(t_app *app)
{
	mlx_hook(app->win, X_ON_KEY, &on_key_press, app);
//    mlx_hook(app->win, 4, 0, &mouse_press, &app);
//    mlx_hook(app->win, 5, 0, &mouse_release, &app);
	mlx_hook(app->win, X_ON_MOUSE_MOVE, &on_mouse_move, app);
	mlx_loop_hook(app->win, &app_loop, app);
//    mlx_hook(app->win, , 0, &app_loop, app);
}

int		app_start(t_app *app, const char *fractal_name, void *mlx)
{
	ft_bzero(app, sizeof(t_app));
	app->win_h = WIN_HEIGHT;
	app->win_w = WIN_WIDTH;
	app->mlx = mlx;
	if (!(ocl_init(&app->ocl)))
	{
		ft_putendl_fd("Failed to initialise OpenCL", 2);
		return (0);
	}
	if (!new_renderer(fractal_name, &app->ren, &app->ocl))
	{
		ft_putendl_fd("Failed to create renderer", 2);
		return (0);
	}
	if (!(app->win = mlx_new_window(app->mlx, app->win_w, app->win_h, (char *)fractal_name)))
	{
		ft_putendl_fd("Failed to create window", 2);
		return (0);
	}
	if (!(app->img = mlx_new_image(app->mlx, app->win_w, app->win_h)))
	{
		ft_putendl_fd("Failed to create image", 2);
		return (0);
	}
	app->pixel_ptr = mlx_get_data_addr(app->img, &app->bits_per_pixel,
			&app->size_line, &app->endian);
	app_connect_events(app);
	return (app_render(app));
}

void	app_finish(t_app *app)
{
	app->win ? mlx_destroy_image(app->mlx, app->img) : 0;
	app->win ? mlx_destroy_window(app->mlx, app->win) : 0;
	delete_renderer(&app->ren);
	ocl_release(&app->ocl);
}
