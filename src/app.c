/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:55:25 by bnesoi            #+#    #+#             */
/*   Updated: 2019/10/18 09:04:47 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				app_render(t_app *app)
{
	app->ren.width = app->win_w;
	app->ren.height = app->win_h;
	if (!render(&app->ren, &app->ocl, app->pixel_ptr))
		return (0);
	if (APPLE)
		mlx_clear_window(app->mlx, app->win);
	mlx_put_image_to_window(app->mlx, app->win, app->img, 0, 0);
	return (1);
}

int				app_error(t_app *app, char *msg)
{
	(void)app;
	ft_putendl_fd(msg, 2);
	return (0);
}

int				app_start(t_app *app, const char *fractal_name,
		void *mlx, const char *custom_gradients)
{
	ft_bzero(app, sizeof(t_app));
	app->win_h = WIN_HEIGHT;
	app->win_w = WIN_WIDTH;
	app->mlx = mlx;
	app->custom_gradient = custom_gradients;
	if (!(ocl_init(&app->ocl)))
		return (app_error(app, "Failed to initialise OpenCL"));
	if (!new_renderer(&app->ren, &app->ocl))
		return (app_error(app, "Failed to create renderer"));
	if (!set_kernel(fractal_name, &app->ren))
		return (app_error(app, HELP));
	if (!app_init_gradients(app))
		return (app_error(app, "Failed to create gradients"));
	if (!(app->win = mlx_new_window(app->mlx, app->win_w, app->win_h,
		(char *)fractal_name)))
		return (app_error(app, "Failed to create window"));
	if (!(app->img = mlx_new_image(app->mlx, app->win_w, app->win_h)))
		return (app_error(app, "Failed to create image"));
	app->pixel_ptr = mlx_get_data_addr(app->img, &app->bits_per_pixel,
			&app->size_line, &app->endian);
	app_connect_events(app);
	return (app_render(app));
}

void			app_finish(t_app *app)
{
	app->img ? mlx_destroy_image(app->mlx, app->img) : 0;
	app->win ? mlx_destroy_window(app->mlx, app->win) : 0;
	delete_renderer(&app->ren);
	app->gradients ? free_gradient_list(&app->gradients) : 0;
	ocl_release(&app->ocl);
	free(app->mlx);
	exit(0);
}
