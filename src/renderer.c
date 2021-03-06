/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:55:25 by bnesoi            #+#    #+#             */
/*   Updated: 2019/10/18 09:09:28 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	log_build_log(t_renderer *ren, t_ocl *ocl)
{
	char	*log;

	log = ocl_get_build_log(ren->program, ocl->device);
	if (log)
	{
		ft_putendl_fd(log, 2);
		free(log);
	}
	return (0);
}

int			new_renderer(t_renderer *ren, t_ocl *ocl)
{
	int		err;

	ren->src = ft_strsplit_any(SRC, " \n");
	ren->src_count = tab_len(ren->src);
	ren->program = ocl_create_program(ocl->context,
			(const char **)ren->src, ren->src_count);
	if (!ren->program || OCL_ERROR(clBuildProgram(
			ren->program, 0, NULL, FCL_INCLUDE, NULL, NULL),
					"Failed to build program"))
		return (log_build_log(ren, ocl));
	#ifdef CL_VERSION_2_0
	ren->queue = clCreateCommandQueueWithProperties(ocl->context,
			ocl->device, 0, &err);
	#else
	ren->queue = clCreateCommandQueue(ocl->context,
			ocl->device, 0, &err);
	#endif
	if (OCL_ERROR(err, "Failed to create queue"))
		return (0);
	ren->zoom = ZOOM;
	ren->iterations = ITERATIONS;
	ren->mouse_x = WIN_WIDTH / 2.0;
	ren->mouse_y = WIN_HEIGHT / 2.0;
	return (1);
}

static int	pre_render(t_renderer *ren, t_ocl *ocl)
{
	int		err;

	err = 0;
	if (!ren->out_mem || ren->width != ren->out_w || ren->height != ren->out_h)
	{
		ren->out_w = ren->height;
		ren->out_h = ren->width;
		ren->out_mem ? clReleaseMemObject(ren->out_mem) : 0;
		ren->out_mem = clCreateBuffer(ocl->context, CL_MEM_READ_WRITE,
				sizeof(cl_int) * ren->out_w * ren->out_h, NULL, &err);
	}
	return (OCL_ERROR(err, "Failed to pre render!") ? 0 : 1);
}

static int	set_kernel_args(t_renderer *ren)
{
	int		err;

	err = clSetKernelArg(ren->kernel, 0, sizeof(cl_float), &ren->zoom);
	err |= clSetKernelArg(ren->kernel, 1, sizeof(cl_float), &ren->mouse_x);
	err |= clSetKernelArg(ren->kernel, 2, sizeof(cl_float), &ren->mouse_y);
	err |= clSetKernelArg(ren->kernel, 3, sizeof(cl_double), &ren->offset_x);
	err |= clSetKernelArg(ren->kernel, 4, sizeof(cl_double), &ren->offset_y);
	err |= clSetKernelArg(ren->kernel, 5, sizeof(cl_int), &ren->width);
	err |= clSetKernelArg(ren->kernel, 6, sizeof(cl_int), &ren->height);
	err |= clSetKernelArg(ren->kernel, 7, sizeof(cl_int), &ren->iterations);
	err |= clSetKernelArg(ren->kernel, 8, sizeof(cl_uint), &ren->gradient_len);
	err |= clSetKernelArg(ren->kernel, 9, sizeof(ren->gradient_mem),
			&ren->gradient_mem);
	err |= clSetKernelArg(ren->kernel, 10, sizeof(ren->out_mem), &ren->out_mem);
	return (OCL_ERROR(err, "Failed to set kernel args!") ? 0 : 1);
}

int			render(t_renderer *ren, t_ocl *ocl, cl_int *result)
{
	int		err;
	size_t	size;

	if (!pre_render(ren, ocl) || !set_kernel_args(ren))
		return (0);
	size = ren->out_w * ren->out_h;
	err = clEnqueueNDRangeKernel(
		ren->queue, ren->kernel, 1, NULL, &size, NULL, 0, NULL, NULL);
	if (OCL_ERROR(err, "Failed to enqueue kernel!"))
		return (0);
	if (OCL_ERROR(clFinish(ren->queue), "Failed to finish queue!"))
		return (0);
	if (OCL_ERROR(clEnqueueReadBuffer(ren->queue, ren->out_mem, CL_TRUE, 0,
			sizeof(cl_int) * size, result, 0, NULL, NULL),
			"Failed to read render output to the surface"))
		return (0);
	return (1);
}
