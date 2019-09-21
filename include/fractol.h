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

# define SCREEN_WIDTH 500
# define SCREEN_HEIGHT 300


typedef struct	s_view t_view;

typedef struct  s_renderer
{
    cl_kernel   kernel;
    cl_float    zoom;
    cl_float    mouse_x;
    cl_float    mouse_y;
    cl_float    offset_x;
    cl_float    offset_y;
    cl_int      width;
    cl_int      height;
    cl_float    iterations;
}               t_renderer;

typedef struct	s_view
{
	SDL_Window	*win;
    t_renderer  *ren;
	void		(*on_event)(SDL_Event *event, t_view *view);
}				t_view;


typedef struct	s_app
{
	t_ocl		ocl;
	t_view		*view;
}				t_app;

#endif
