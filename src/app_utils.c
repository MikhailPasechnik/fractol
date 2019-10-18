/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 08:58:56 by bnesoi            #+#    #+#             */
/*   Updated: 2019/10/18 09:02:13 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		on_win_close(t_app *app)
{
	app_finish(app);
	exit(0);
}

void			app_connect_events(t_app *app)
{
	mlx_hook(app->win, X_ON_KEY, &on_key_press, app);
	mlx_hook(app->win, X_ON_WIN_CLOSE, &on_win_close, app);
	mlx_hook(app->win, X_ON_MOUSE_MOVE, &on_mouse_move, app);
	mlx_hook(app->win, X_ON_MOUSE_WHEEL, &on_mouse_wheel, app);
	mlx_loop_hook(app->mlx, animation_loop_callback, app);
}

int				app_init_gradients(t_app *app)
{
	char	*gradients;

	if ((gradients = fio_read_file(GRADIENTS_TXT, NULL)) == NULL)
		return (0);
	app->gradients = gradients_from_str(gradients);
	if (app->custom_gradient)
		gradient_add(
			&app->gradients,
			gradients_from_str((char *)app->custom_gradient));
	free(gradients);
	if (!app->gradients)
		return (0);
	app->gradients_head = app->gradients;
	return (set_gradient(
		&app->ren, &app->ocl, app->gradients->data, app->gradients->len));
}
