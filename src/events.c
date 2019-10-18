/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 08:59:05 by bnesoi            #+#    #+#             */
/*   Updated: 2019/10/18 09:06:28 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				on_mouse_move(int x, int y, t_app *app)
{
	if (app->animation_callback)
		return (1);
	app->ren.mouse_x = (app->win_w / 2.0 - x);
	app->ren.mouse_y = (app->win_h / 2.0 - y);
	app_render(app);
	return (1);
}

int				on_mouse_wheel(int btn, int x, int y, t_app *app)
{
	(void)x;
	(void)y;
	if (!(btn == 4 || btn == 5))
		return (1);
	app->ren.zoom += (btn == 4 ? 1.0 : -1.0) * 4.0 * app->ren.zoom / 100.0;
	app->ren.zoom = app->ren.zoom > 0 ? app->ren.zoom : 1;
	app_render(app);
	return (1);
}

static int		on_key_press2(int key, t_app *app, int *update)
{
	if (key == KEY_O || key == KEY_I)
	{
		app->ren.zoom += (key == KEY_I ? 1.0 : -1.0)
				* 4.0 * app->ren.zoom / 100.0;
		app->ren.zoom = app->ren.zoom > 0 ? app->ren.zoom : 1;
		*update = 1;
	}
	else if (key == KEY_S)
	{
		if (!save_image(
				app->ren.kernel_name, app->pixel_ptr, app->win_w, app->win_h))
			ft_fprintf(2, "Failed to save image\n");
		else
			ft_printf("Fractal saved to: %s.pgm\n", app->ren.kernel_name);
	}
	return (1);
}

static int		on_key_press1(int key, t_app *app, int *update)
{
	if (key == KEY_0)
		app->animation_callback = NULL;
	else if (key == KEY_1)
		app->animation_callback = julia_animation_callback;
	else if (key == KEY_2)
		app->animation_callback = julia_animation_callback1;
	else if (key == KEY_3)
		app->animation_callback = julia_animation_callback2;
	else if (key == KEY_G)
	{
		if (!app->gradients->next)
			app->gradients = app->gradients_head;
		else
			app->gradients = app->gradients->next;
		set_gradient(&app->ren, &app->ocl, app->gradients->data,
				app->gradients->len);
		*update = 1;
	}
	return (on_key_press2(key, app, update));
}

int				on_key_press(int key, t_app *app)
{
	int	update;

	update = 0;
	if (key == KEY_ESC)
		app_finish(app);
	else if (key == KEY_PLUS || (key == KEY_MINUS && app->ren.iterations > 0))
	{
		app->ren.iterations += key == KEY_PLUS ? 1 : -1;
		update = 1;
	}
	else if (key == KEY_LEFT || key == KEY_RIGHT)
	{
		app->ren.offset_x += (key == KEY_RIGHT ? 7.0l : -7.0l) / app->ren.zoom;
		update = 1;
	}
	else if (key == KEY_DOWN || key == KEY_UP)
	{
		app->ren.offset_y += (key == KEY_UP ? 7.0l : -7.0l) / app->ren.zoom;
		update = 1;
	}
	on_key_press1(key, app, &update);
	if (update)
		app_render(app);
	return (1);
}
