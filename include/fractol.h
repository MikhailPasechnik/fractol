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
# include "file_io.h"
# include "ocl.h"
# include "mlx.h"
# include "gradient.h"

# define WIN_WIDTH 800
# define WIN_HEIGHT 500
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

	# define KEY_1 18
	# define KEY_2 19
	# define KEY_3 20
	# define KEY_4 21
	# define KEY_5 23
	# define KEY_6 22
	# define KEY_7 26
	# define KEY_8 28
	# define KEY_9 25
	# define KEY_0 29
    # define KEY_G 25

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

	# define KEY_1 XK_1
	# define KEY_2 XK_2
	# define KEY_3 XK_3
	# define KEY_4 XK_4
	# define KEY_5 XK_5
	# define KEY_6 XK_6
	# define KEY_7 XK_7
	# define KEY_8 XK_8
	# define KEY_9 XK_9
	# define KEY_0 XK_0
	# define KEY_G XK_g

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
# define BURNING_SHIP "burning_ship"
# define JULIA "julia"
# ifdef __APPLE__
	# define FCL_INCLUDE "-I res/cl"
# else
	# define FCL_INCLUDE "-I./res/cl"
# endif
// TODO: Compile all kernels at ones
# define GRADIENTS_TXT "res/gradients.txt"
# define FCL_SRC "res/cl/complex.cl res/cl/utils.cl"
# define MANDELBROT_SRC FCL_SRC" res/cl/"MANDELBROT".cl"
# define JULIA_SRC FCL_SRC" res/cl/"JULIA".cl"
# define BURNING_SHIP_SRC FCL_SRC" res/cl/"BURNING_SHIP".cl"

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

	cl_mem              gradient_mem;
	cl_uchar4           *gradient;
	cl_uint             gradient_len;


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

	const char                *custom_gradient;
	t_gradient          *gradients;
	t_gradient          *gradients_head;

	long long           time;
    void (*animation_callback)(struct s_app *);
}				t_app;

/*
** App functions
*/
int		        app_start(t_app *app, const char *fractal_name, void *mlx, const char *custom_gradients);
void			app_finish(t_app *app);
int             app_render(t_app *app);


/*
** Render functions
*/
int				new_renderer(const char *name, t_renderer *ren, t_ocl *ocl);
void			delete_renderer(t_renderer *ren);
int				render(t_renderer *ren, t_ocl *ocl, cl_int *result);
int             set_gradient(t_renderer *ren, t_ocl *ocl,
        cl_uchar4 *gradient, cl_uint gradient_len);


/*
** Utils functions
*/
size_t			tab_len(char **tab);
void            *tab_free(char **tab);
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
void    julia_animation_callback1(t_app  *app);
void    julia_animation_callback2(t_app  *app);

#endif
