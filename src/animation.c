/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 08:58:49 by bnesoi            #+#    #+#             */
/*   Updated: 2019/10/18 09:01:27 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <sys/time.h>

static long long	current_timestamp(void)
{
	struct timeval	te;

	gettimeofday(&te, NULL);
	return (te.tv_sec * 1000LL + te.tv_usec / 1000);
}

int					animation_loop_callback(t_app *app)
{
	if (!app->animation_callback)
		return (1);
	if (!app->time)
	{
		app->time = current_timestamp();
		return (1);
	}
	if (current_timestamp() - app->time < 25)
		return (1);
	app->animation_callback(app);
	app->time = current_timestamp();
	return (1);
}

void				julia_animation_callback(t_app *app)
{
	app->ren.mouse_y = (sin((double)app->time / 11000)) * (WIN_HEIGHT / 5);
	app->ren.mouse_x = (tan((double)(app->time + 25) / 6000)) * (WIN_WIDTH / 5);
	app_render(app);
}

void				julia_animation_callback1(t_app *app)
{
	app->ren.mouse_y = (sin((double)app->time / 11000)) * (WIN_HEIGHT / 4);
	app->ren.mouse_x = (cos((double)(app->time + 25) / 6000)) * (WIN_WIDTH / 4);
	app_render(app);
}

void				julia_animation_callback2(t_app *app)
{
	app->ren.mouse_y = -(atan((double)app->time / 12000)) * (WIN_HEIGHT / 5);
	app->ren.mouse_x = (
		tan((double)(app->time + 25) / 11000)) * (WIN_WIDTH / 5);
	app_render(app);
}
