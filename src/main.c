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

int		sdl_init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
	{
		ft_putendl_fd("Failed to init SDL! SDL_Error: ", 2);
		ft_putendl_fd(SDL_GetError(), 2);
		return (0);
	}
	return (1);
}

void	sdl_loop(t_app *app)
{
	SDL_Event event;

	while (SDL_PollEvent(&event) && event.type != SDL_QUIT)
	{
		if (event.type == SDL_WINDOWEVENT && SDL_GetWindowID(app->win) == event.window.windowID)
			on_app_event(app, &event);
	}
}

int _main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	!sdl_init() ? exit(1) : 0;
	SDL_Window *window = NULL;
	//Create window
	if ((window = SDL_CreateWindow("SDL Tutorial",
								   SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH,
								   WIN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE)) == NULL)
	{
		ft_putendl_fd("Window could not be created! SDL_Error: ", 2);
		ft_putendl_fd(SDL_GetError(), 2);
		exit(1);
	}
	//The surface contained by the window
	SDL_Surface *screenSurface = NULL;
	//Get window surface
	screenSurface = SDL_GetWindowSurface(window);
	//Fill the surface white
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
	//Update the surface
	SDL_UpdateWindowSurface(window);

	t_ocl ocl;
	ocl_init(&ocl);

	int i;
	SDL_PixelFormat *fmt;
	fmt = screenSurface->format;
	i = 0;
	Uint32 *pixels = ((Uint32 *) screenSurface->pixels);
	while (i < WIN_HEIGHT * WIN_WIDTH / 2)
	{
		pixels[i] = SDL_MapRGBA(fmt, 0, 0, 255, 255);
		i++;
	}
	SDL_UpdateWindowSurface(window);
	SDL_Delay(2000);
	i = 0;
	while (i < WIN_HEIGHT * WIN_WIDTH)
	{
		pixels[i] = SDL_MapRGBA(fmt, 255, 0, 255, 255);
		i++;
	}

	SDL_Event event;
	int quit = 0;
	SDL_UpdateWindowSurface(window);

	while (!quit)
	{
		while (SDL_PollEvent(&event) != 0)
		{

			quit = event.type == SDL_QUIT;
			printf("event.type: %d\n", event.type);
			if (quit)
			{
				printf("event.type == SDL_QUIT: %d\n", event.type == SDL_QUIT);
			}
			if (event.type == SDL_WINDOWEVENT)
			{
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				{
					printf("event.type == SDL_WINDOWEVENT_SIZE_CHANGED: %d\n",
						   screenSurface->pitch);
					screenSurface = SDL_GetWindowSurface(window);
					SDL_FillRect(screenSurface, NULL,
								 SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
					SDL_UpdateWindowSurface(window);
				}
			} else if (event.type == SDL_MOUSEMOTION && event.motion.state & SDL_BUTTON_LMASK)
			{
				printf("SDL_MOUSEMOTION: x:%d y:%d\n", event.motion.x, event.motion.y);
			} else if (event.type == SDL_MOUSEBUTTONDOWN)
				printf("SDL_MOUSE UP/DOWN: key: %d\n", event.button.button);
		}
	}

	SDL_DestroyWindow(window);
	ocl_release(&ocl);
	SDL_Quit();
	return (0);
}

int main(int argc, char **argv)
{
	t_app app;

	if (argc < 2 || argc > 2)
		ft_putendl(USAGE);
	else if (ft_strcmp(argv[1], HELP_ARG) == 0)
		ft_putendl(HELP);
	else
	{
		!sdl_init() ? exit(1) : 0;
		if (!app_start(&app, argv[1]))
			app_finish(&app);
		else
		{
			sdl_loop(&app);
			app_finish(&app);
		}
		SDL_Quit();
	}
	return (0);
}
