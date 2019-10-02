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

int		app_start(t_app *app, const char *fractal_name)
{
	ft_bzero(app, sizeof(t_app));
	if (!(app->win = SDL_CreateWindow(
			fractal_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			WIN_WIDTH, WIN_HEIGHT, WIN_FLAGS)))
	{
		ft_putendl_fd("Window could not be created! SDL_Error: ", 2);
		ft_putendl_fd(SDL_GetError(), 2);
		return (0);
	}
	app->win_h = WIN_HEIGHT;
	app->win_w = WIN_WIDTH;
	SDL_GetWindowSize(app->win, &app->win_w, &app->win_w);
	if (!(ocl_init(&app->ocl)))
	{
		ft_putendl_fd("Failed to initialise OpenCL", 2);
		return (0);
	}
	if (!new_renderer(fractal_name, app))
	{
		ft_putendl_fd("Failed to create renderer", 2);
		return (0);
	}
	return (1);
}

void	app_finish(t_app *app)
{
	app->win ? SDL_DestroyWindow(app->win) : 0;
	delete_renderer(&app->ren);
	ocl_release(&app->ocl);
}
void	on_app_event(t_app *app, SDL_Event *event)
{
	if (event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
		SDL_GetWindowSize(app->win, &app->win_w, &app->win_w);
}
