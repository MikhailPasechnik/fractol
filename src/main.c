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

int sdl_init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
	{
		ft_putendl_fd("Failed to init SDL! SDL_Error: ", 2);
		ft_putendl_fd(SDL_GetError(), 2);
		return (0);
	}
	return (1);
}

t_view *get_view_from_winid(Uint32 id, t_app *app)
{
	int i;
	t_view *v;

	i = 0;
	while (i < MAX_VIEW)
	{
		v = app->views[i];
		if (v != NULL && SDL_GetWindowID(v->win) == id)
			return (v);
		i++;
	}
	return (NULL);
}


t_view *open_view(unsigned int w, unsigned int h, const char *name, t_app *app)
{
	t_view *v;
	int i;

	if (app->view_count >= MAX_VIEW)
		return (NULL);
	if (!(v = ft_memalloc(sizeof(*v))))
		return (NULL);
	if (!(v->win = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
									w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE)))
	{
		ft_putendl_fd("Window could not be created! SDL_Error: ", 2);
		ft_putendl_fd(SDL_GetError(), 2);
		free(v);
		return (NULL);
	}
	app->view_count++;

	i = -1;
	while (++i < MAX_VIEW)
		if (!app->views[i])
		{
			app->views[i] = v;
			break;
		}
	return (v);
}

void sdl_loop(t_app *app)
{
	SDL_Event event;
	t_view *view;

	int quit = 0;
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_WINDOWEVENT && (view = get_view_from_winid(
					event.window.windowID, app)))
				view->on_event ? view->on_event(&event, view) : 0;
		}
		if (!app->view_count)
			quit = 1;
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
								   SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
								   SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE)) == NULL)
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
	while (i < SCREEN_HEIGHT * SCREEN_WIDTH / 2)
	{
		pixels[i] = SDL_MapRGBA(fmt, 0, 0, 255, 255);
		i++;
	}
	SDL_UpdateWindowSurface(window);
	SDL_Delay(2000);
	i = 0;
	while (i < SCREEN_HEIGHT * SCREEN_WIDTH)
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

#include <complex.h>
#include <assert.h>
#include <math.h>

typedef struct s_complex
{
	cl_float r;
	cl_float i;

} t_complex;

t_complex c_add(t_complex a, t_complex b);

t_complex c_sub(t_complex a, t_complex b);

t_complex c_mul(t_complex a, t_complex b);

t_complex c_div(t_complex a, t_complex b);

t_complex c_abs(t_complex a);

inline t_complex c_add(t_complex a, t_complex b)
{
	return ((t_complex) {a.r + b.r, a.i + b.i});
}

inline t_complex c_sub(t_complex a, t_complex b)
{
	return ((t_complex) {a.r - b.r, a.i - b.i});
}

inline t_complex c_mul(t_complex a, t_complex b)
{
	return ((t_complex) {a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r});
}

inline t_complex c_div(t_complex a, t_complex b)
{
	return (t_complex) {
		(a.r * b.r + a.i * b.i) / (b.r * b.r + b.i * b.i),
		(a.i * b.r - a.r * b.i) / (b.r * b.r + b.i * b.i)
	};
}

inline t_complex c_abs(t_complex a)
{
	return ((t_complex) {hypot(a.r, a.i), 0});
}


int test_complex_cl()
{
	double complex aa = 10 + 2 * I;
	double complex bb = -3 - 10 * I;
	double complex cc;

	cc = aa + bb;
	printf("(%f %f) + (%f %f) = (%f %f)\n",
		   creal(aa), cimag(aa), creal(bb), cimag(bb), creal(cc), cimag(cc));

	printf("abs((%f %f)) = (%f %f)\n", creal(cc), cimag(cc), creal(cabs(cc)), cimag(cabs(cc)));

	cc = aa - bb;
	printf("(%f %f) - (%f %f) = (%f %f)\n",
		   creal(aa), cimag(aa), creal(bb), cimag(bb), creal(cc), cimag(cc));

	cc = aa / bb;
	printf("(%f %f) / (%f %f) = (%f %f)\n",
		   creal(aa), cimag(aa), creal(bb), cimag(bb), creal(cc), cimag(cc));

	cc = aa * bb;
	printf("(%f %f) * (%f %f) = (%f %f)\n\n\n",
			creal(aa), cimag(aa), creal(bb), cimag(bb), creal(cc), cimag(cc));


	t_ocl		ocl;
	cl_program	program;
	cl_kernel 	kernel;
	int			err;
	size_t 		global;

	ocl_init(&ocl);
	char	*src[20] = {
			"src/cl/complex.c",
			"src/cl/test_complex.c",
	};
	program = ocl_create_program(ocl.context, (const char **)src, 2);
	if (!program  || OCL_ERROR2(clBuildProgram(program, 0, NULL, "-I./src/cl", NULL, NULL)))
		exit(1);
	kernel = clCreateKernel(program, "test_complex", &err);
	if (OCL_ERROR2(err))
		exit(1);
	global = 1;
	if (OCL_ERROR2(clEnqueueNDRangeKernel(ocl.queue, kernel, 1u, NULL, &global, NULL, 0, NULL, NULL)))
		exit(1);
	clFinish(ocl.queue);
	return (0);
}

int main(int argc, char **argv)
{
	test_complex_cl();
	return (0);
}
