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
# define ITERATIONS 100;
# define ZOOM 1;

# define HELP_ARG "help"
# define USAGE "./fractol "HELP_ARG
# define HELP "./fractol mandelbrot | julia"

# define MANDELBROT "mandelbrot"
# define JULIA "julia"

# define SRC "src/cl/complex.cl src/cl/utils.cl"
# define MANDELBROT_SRC SRC" src/cl/"MANDELBROT".cl"
# define JULIA_SRC SRC" src/cl/"JULIA".cl"

typedef struct	s_renderer
{
	cl_kernel			kernel;
	cl_program			program;
	cl_command_queue	queue;

	char				*kernel_name;
	char				**src;
	size_t				src_count;

	cl_float			zoom;
	cl_float			mouse_x;
	cl_float			mouse_y;
	cl_float			offset_x;
	cl_float			offset_y;
	cl_int				width;
	cl_int				height;
	cl_int				iterations;

	cl_mem				out_mem;
	int					out_w;
	int					out_h;
}               t_renderer;

typedef struct	s_app
{
	SDL_Window			*win;
	int					win_w;
	int					win_h;

	t_renderer			ren;
	t_ocl				ocl;
}				t_app;

/*
** App functions
*/
int				app_start(t_app *app, const char *fractal_name);
void			app_finish(t_app *app);
void			on_app_event(t_app *app, SDL_Event *event);


/*
** Render functions
*/
int				new_renderer(const char *name, t_app *app);
void			delete_renderer(t_renderer *ren);
void			render(t_app *app);


/*
** Utils functions
*/
size_t			tab_len(const char **tab);
int				pick_fractal(const char *name, t_renderer *ren);


/*
** Event functions
*/
void	on_mouse_move(SDL_Event *event, t_app *app, int *changed);
void	on_window_size_change(SDL_Event *event, t_app *app, int *changed);
void	on_mouse_wheel(SDL_Event *event, t_app *app, int *changed);

#endif
