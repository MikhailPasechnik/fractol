/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 08:59:30 by bnesoi            #+#    #+#             */
/*   Updated: 2019/10/18 09:00:15 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			set_kernel(const char *kernel_name, t_renderer *ren)
{
	int			err;
	cl_kernel	k;
	char		*name;

	k = clCreateKernel(ren->program, kernel_name, &err);
	if (OCL_ERROR(err, "Failed to create kernel"))
		return (0);
	if ((name = ft_strdup(kernel_name)) == NULL)
		return (0);
	ren->kernel_name ? free(ren->kernel_name) : 0;
	ren->kernel_name = name;
	ren->kernel ? clReleaseKernel(ren->kernel) : 0;
	ren->kernel = k;
	return (1);
}

void		delete_renderer(t_renderer *ren)
{
	ren->queue ? clReleaseCommandQueue(ren->queue) : 0;
	ren->out_mem ? clReleaseMemObject(ren->out_mem) : 0;
	ren->gradient_mem ? clReleaseMemObject(ren->gradient_mem) : 0;
	ren->kernel ? clReleaseKernel(ren->kernel) : 0;
	ren->program ? clReleaseProgram(ren->program) : 0;
	ren->kernel_name ? ft_strdel(&ren->kernel_name) : 0;
	while (ren->src_count--)
		ft_strdel(&ren->src[ren->src_count]);
	ren->src ? ft_memdel((void **)&ren->src) : 0;
}

int			set_gradient(t_renderer *ren, t_ocl *ocl,
		cl_uchar4 *gradient, cl_uint gradient_len)
{
	int	err;

	ren->gradient = gradient;
	ren->gradient_len = gradient_len;
	ren->gradient_mem ? clReleaseMemObject(ren->gradient_mem) : 0;
	ren->gradient_mem = clCreateBuffer(
			ocl->context, CL_MEM_READ_ONLY,
			sizeof(cl_uchar4) * ren->gradient_len, NULL, &err);
	err |= clEnqueueWriteBuffer(
			ren->queue, ren->gradient_mem, CL_TRUE, 0,
			sizeof(cl_uchar4) * ren->gradient_len,
			ren->gradient, 0, NULL, NULL);
	return (OCL_ERROR(err, "Failed to set gradient!") ? 0 : 1);
}
