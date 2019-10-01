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
	if (!ren->out || app->win_w != ren->out_w || app->win_h != ren->out_h)
	{
		app->ren.out ? clReleaseMemObject(ren->out) : 0;
		app->ren.out = clCreateBuffer(
				app->ocl.context, CL_MEM_READ_WRITE,
				sizeof(cl_int) * app->win_h * app->win_h, NULL, &err);
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
	err |= clSetKernelArg(ren->kernel, 8, sizeof(ren->out), &ren->out);
	return (OCL_ERROR(err, "Failed to set kernel args!") ? 0 : 1);
}

void			render(t_app *app)
{
	int err;

	// Pre render
	pre_render(app);
	// Set kernel params
	set_kernel_args(app);
	// Enqueue surface
	// Set surface from re
}
