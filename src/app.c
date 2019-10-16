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
		return (0);
	if (APPLE)
    	mlx_clear_window(app->mlx, app->win);
	mlx_put_image_to_window(app->mlx, app->win, app->img, 0, 0);
	return (1);
}

static int on_win_close(t_app *app)
{
	app_finish(app);
	exit(0);
}

static void app_connect_events(t_app *app)
{
	mlx_hook(app->win, X_ON_KEY, &on_key_press, app);
	mlx_hook(app->win, X_ON_WIN_CLOSE, &on_win_close, app);
	mlx_hook(app->win, X_ON_MOUSE_MOVE, &on_mouse_move, app);
	mlx_hook(app->win, X_ON_MOUSE_WHEEL, &on_mouse_wheel, app);
    mlx_loop_hook(app->mlx, animation_loop_callback, app);
}

int     app_init_gradients(t_app *app)
{
    char    *gradients;

    if((gradients = fio_read_file(GRADIENTS_TXT, NULL)) == NULL)
        return (0);
    app->gradients = gradients_from_str(gradients);
    if (app->custom_gradient)
        gradient_add(&app->gradients, gradients_from_str((char *)app->custom_gradient));
    free(gradients);
    if (!app->gradients)
        return (0);
    app->gradients_head = app->gradients;
    return (set_gradient(&app->ren, &app->ocl, app->gradients->data, app->gradients->len));
}

int     app_error(t_app* app, char *msg)
{
    ft_putendl_fd(msg, 2);
    return (0);
}

int		app_start(t_app *app, const char *fractal_name, void *mlx, const char *custom_gradients)
{
	ft_bzero(app, sizeof(t_app));
	app->win_h = WIN_HEIGHT;
	app->win_w = WIN_WIDTH;
	app->mlx = mlx;
	app->custom_gradient = custom_gradients;
	if (!(ocl_init(&app->ocl)))
        return (app_error(app, "Failed to initialise OpenCL"));
	if (!new_renderer(fractal_name, &app->ren, &app->ocl))
        return (app_error(app, "Failed to create renderer"));
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

void	app_finish(t_app *app)
{
	app->img ? mlx_destroy_image(app->mlx, app->img) : 0;
	app->win ? mlx_destroy_window(app->mlx, app->win) : 0;
	delete_renderer(&app->ren);
	app->gradients ? free_gradient_list(&app->gradients) : 0;
	ocl_release(&app->ocl);
	free(app->mlx);
	exit(0);
}
