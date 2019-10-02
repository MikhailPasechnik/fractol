/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:55:25 by bnesoi            #+#    #+#             */
/*   Updated: 2019/06/21 12:52:38 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int     new_renderer(const char *name, t_app *app)
{
	int			err;
	t_renderer	*ren;

	ren = &app->ren;
	if (!pick_fractal(name, ren))
	{
		ft_putendl_fd("Failed to pick fractal", 2);
		return (0);
	}
	ren->program = ocl_create_program(app->ocl.context,
			(const char **)ren->src, ren->src_count);
	if (!ren->program || OCL_ERROR(clBuildProgram(
			ren->program, 0, NULL, "-I./src/cl", NULL, NULL),
					"Failed to build program"))
		return (0);
	ren->kernel = clCreateKernel(ren->program, ren->kernel_name, &err);
	if (OCL_ERROR(err, "Failed to create kernel"))
		return (0);
	ren->queue = clCreateCommandQueue(app->ocl.context,
			app->ocl.device, NULL, &err);
	if (OCL_ERROR(err, "Failed to create queue"))
		return (0);
	ren->zoom = ZOOM;
	ren->iterations = ITERATIONS;
	ren->mouse_x = app->win_w / 2.0;
	ren->mouse_y = app->win_h / 2.0;
	return (1);
}

void    delete_renderer(t_renderer *ren)
{
	ren->queue ? clReleaseCommandQueue(ren->queue) : 0;
	ren->kernel ? clReleaseKernel(ren->kernel) : 0;
	ren->program ? clReleaseProgram(ren->program) : 0;
	ren->kernel_name ? ft_strdel(&ren->kernel_name) : 0;
	while (ren->src_count--)
		ft_strdel(&ren->src[ren->src_count]);
	ren->src ? ft_memdel((void **)&ren->src) : 0;
}

static int	pre_render(t_app *app)
{
	int			err;
	t_renderer	*ren;

	ren = &app->ren;
	err = 0;
	if (!ren->out_mem || app->win_w != ren->out_w || app->win_h != ren->out_h)
	{
//	    ren->result ? ft_memdel((void **)&ren->result) : 0;
        ren->out_mem ? clReleaseMemObject(ren->out_mem) : 0;
		ren->out_mem = clCreateBuffer(
				app->ocl.context, CL_MEM_READ_WRITE,
				sizeof(cl_int) * app->win_w * app->win_h, NULL, &err);
		ren->out_w = app->win_w;
		ren->out_h = app->win_h;
		ren->width = app->win_w;
		ren->height = app->win_h;
//		if (!(ren->result = malloc(sizeof(cl_int) * app->win_w * app->win_h)))
//		{
//		    ft_putendl_fd("Failed to allocate render result!", 2);
//            return 0;
//        }
	}
	return (OCL_ERROR(err, "Failed to pre render!") ? 0 : 1);
}

static int set_kernel_args(t_app *app)
{
	int			err;
	t_renderer	*ren;

	ren = &app->ren;
	err = clSetKernelArg(ren->kernel, 0, sizeof(cl_float), &ren->zoom);
	err |= clSetKernelArg(ren->kernel, 1, sizeof(cl_float), &ren->mouse_x);
	err |= clSetKernelArg(ren->kernel, 2, sizeof(cl_float), &ren->mouse_y);
	err |= clSetKernelArg(ren->kernel, 3, sizeof(cl_float), &ren->offset_x);
	err |= clSetKernelArg(ren->kernel, 4, sizeof(cl_float), &ren->offset_y);
	err |= clSetKernelArg(ren->kernel, 5, sizeof(cl_int), &ren->width);
	err |= clSetKernelArg(ren->kernel, 6, sizeof(cl_int), &ren->height);
	err |= clSetKernelArg(ren->kernel, 7, sizeof(cl_int), &ren->iterations);
	err |= clSetKernelArg(ren->kernel, 8, sizeof(ren->out_mem), &ren->out_mem);
	return (OCL_ERROR(err, "Failed to set kernel args!") ? 0 : 1);
}

void			render(t_app *app)
{
	int	err;
	size_t size;

	// Pre render
	pre_render(app);
	// Set kernel params
	set_kernel_args(app);
	printf("zoom: %f\nmouse_x: %f\nmouse_y: %f\noffset_x: %f\noffset_y: %f\nwidth: %d\nheight: %d\niterations: %d\n",
		   app->ren.zoom, app->ren.mouse_x, app->ren.mouse_y, app->ren.offset_x, app->ren.offset_y, app->ren.width, app->ren.height, app->ren.iterations);
	// Enqueue surface
	size = app->win_w * app->win_h;
	err = clEnqueueNDRangeKernel(app->ren.queue, app->ren.kernel,
			1, NULL, &size, NULL, 0, NULL, NULL);
	if (OCL_ERROR(err, "Failed to enqueue render surface!"))
		return ;
	if OCL_ERROR(clFinish(app->ren.queue), "Failed to finish queue!")
		return ;
	SDL_Surface *surface;
	surface = SDL_GetWindowSurface(app->win);
	if (OCL_ERROR(clEnqueueReadBuffer(app->ren.queue, app->ren.out_mem, CL_TRUE, 0,
					sizeof(cl_int) * size, surface->pixels, 0, NULL, NULL
			), "Failed to read render output to the surface"))
		return ;
//	SDL_PixelFormat *fmt;
//    fmt = surface->format;
//    Uint32 *pixels = ((Uint32*)surface->pixels);
//    while (size--)
//        pixels[size] = SDL_MapRGB(
//                fmt,
//                app->ren.result[size] >> 16 & 0xFF,
//                app->ren.result[size] >> 8 & 0xFF,
//                app->ren.result[size] & 0xFF);
	SDL_UpdateWindowSurface(app->win);
}
