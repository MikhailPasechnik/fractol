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
# include "ocl.h"
# include "mlx.h"

# define WIN_WIDTH 840
# define WIN_HEIGHT 480
# define ITERATIONS 50
# define ZOOM 1


/*
** Key codes
*/
# ifdef __APPLE__
    # define APPLE 1
	# define X_ON_KEY 2, 0
	# define X_ON_MOUSE_MOVE 6, 0
	# define X_ON_MOUSE_WHEEL 4, 0
	# define X_ON_WIN_CLOSE 17, 0
	# define KEY_PLUS 69
	# define KEY_MINUS 78
	# define KEY_W 13
	# define KEY_A 0
	# define KEY_S 1
	# define KEY_D 2
	# define KEY_Q 12
	# define KEY_E 14
	# define KEY_R 15
	# define KEY_T 17
	# define KEY_Y 16
	# define KEY_U 32
	# define KEY_V 9
	# define KEY_UP 125
	# define KEY_LEFT 123
	# define KEY_RIGHT 124
	# define KEY_DOWN 126
	# define KEY_ESC 53
# else
    # define APPLE 0
	# include <X11/X.h>
	# include <X11/keysym.h>
	# define X_ON_KEY KeyPress, KeyPressMask
	# define X_ON_MOUSE_MOVE MotionNotify, PointerMotionMask
	# define X_ON_MOUSE_WHEEL 4, 0
	# define X_ON_WIN_CLOSE 17, 0
	# define KEY_PLUS XK_equal
	# define KEY_MINUS XK_minus
	# define KEY_W 119
	# define KEY_A 97
	# define KEY_S 115
	# define KEY_D 100
	# define KEY_Q 113
	# define KEY_E 101
	# define KEY_R 114
	# define KEY_T 116
	# define KEY_Y 121
	# define KEY_U 117
	# define KEY_V 118
	# define KEY_UP XK_Up
	# define KEY_LEFT XK_Left
	# define KEY_RIGHT XK_Right
	# define KEY_DOWN XK_Down
	# define KEY_ESC XK_Escape
# endif


/*
** Usage
*/
# define HELP_ARG "help"
# define USAGE "./fractol "HELP_ARG
# define HELP "./fractol mandelbrot | julia"


/*
** Fractal source setup
*/
# define MANDELBROT "mandelbrot"
# define JULIA "julia"
# ifdef __APPLE__
	# define FCL_INCLUDE "-I src/cl"
# else
	# define FCL_INCLUDE "-I./src/cl"
# endif
# define FCL_SRC "src/cl/complex.cl src/cl/utils.cl"
# define MANDELBROT_SRC FCL_SRC" src/cl/"MANDELBROT".cl"
# define JULIA_SRC FCL_SRC" src/cl/"JULIA".cl"

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
	cl_double	        offset_x;
	cl_double			offset_y;
	cl_int				width;
	cl_int				height;
	cl_int				iterations;

	cl_mem				out_mem;
	int					out_w;
	int					out_h;
}               t_renderer;

typedef struct	s_app
{
	void		        *mlx;
	void                *win;
	void                *img;
	void                *pixel_ptr;
	int                 bits_per_pixel;
	int                 size_line;
	int                 endian;
	int					win_w;
	int					win_h;

	t_renderer			ren;
	t_ocl				ocl;

	long long           time;
    void (*animation_callback)(struct s_app *);
}				t_app;

/*
** App functions
*/
int				app_start(t_app *app, const char *fractal_name, void *mlx);
void			app_finish(t_app *app);
int             app_render(t_app *app);


/*
** Render functions
*/
int				new_renderer(const char *name, t_renderer *ren, t_ocl *ocl);
void			delete_renderer(t_renderer *ren);
int				render(t_renderer *ren, t_ocl *ocl, cl_int *result);


/*
** Utils functions
*/
size_t			tab_len(const char **tab);
int				pick_fractal(const char *name, t_renderer *ren);


/*
** Event functions
*/
int     on_mouse_move(int x, int y, t_app *app);
int     on_mouse_wheel(int btn, int x, int y, t_app *app);
int     on_key_press(int key, t_app *app);

/*
** Animation bonus
*/
int     animation_loop_callback(t_app *app);
void    julia_animation_callback(t_app  *app);

#endif
