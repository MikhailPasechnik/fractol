/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:13:17 by bnesoi            #+#    #+#             */
/*   Updated: 2019/07/14 16:38:37 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <stdio.h>

# include "libft.h"
# include "keys.h"
# include "ocl.h"
# include "SDL.h"

# define WIN_WIDTH 500
# define WIN_HEIGHT 300
# define WIN_FLAGS SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE

# define HELP_ARG "help"
# define USAGE "./fractol "HELP_ARG
# define HELP "./fractol mandelbrot | julia"

# define MANDELBROT "mandelbrot"
# define MANDELBROT_SRC "src/cl/complex.c src/cl/"MANDELBROT".c"
# define JULIA "julia"
# define JULIA_SRC "src/cl/complex.c src/cl/"JULIA".c"

typedef struct  s_renderer
{
	cl_kernel           kernel;
	cl_program	        program;
	cl_command_queue    queue;

	char          *kernel_name;
	char                **src;
	size_t              src_count;

	cl_float            zoom;
	cl_float            mouse_x;
	cl_float            mouse_y;
	cl_float            offset_x;
	cl_float            offset_y;
	cl_int              width;
	cl_int              height;
	cl_float            iterations;
}               t_renderer;

typedef struct	s_app
{
	SDL_Window	        *win;
	t_renderer          ren;
	t_ocl		        ocl;
}				t_app;

/*
** App functions
*/
int     app_start(t_app *app, const char *fractal_name);
void    app_finish(t_app *app);
void    on_app_event(t_app *app, SDL_Event *event);


/*
** Render functions
*/
int     new_renderer(
		const char *name,
		t_renderer *ren,
		cl_device_id device,
		cl_context context
);
void    delete_renderer(t_renderer *ren);

#endif
