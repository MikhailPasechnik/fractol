/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 09:18:53 by bnesoi            #+#    #+#             */
/*   Updated: 2019/10/18 09:19:15 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OCL_H
# define OCL_H
# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/opencl.h>
# endif
# include "libft.h"

# define CL_TARGET_OPENCL_VERSION 220

cl_device_id	ocl_create_device();
cl_program		ocl_create_program(cl_context ctx,
	const char **file_names, size_t count);

typedef struct	s_ocl
{
	cl_device_id		device;
	cl_context			context;
}				t_ocl;

int				ocl_init(t_ocl *cl);
void			ocl_release(t_ocl *cl);
char			*ocl_get_build_log(cl_program program, cl_device_id device_id);
void			ocl_log_program_build(cl_program program,
	cl_device_id device_id, int fd);
const char		*ocl_get_error_string(cl_int error);

int				ocl_put_error(int err, const char *msg,
		const char *file, int line);

# define OCL_PUT_ERROR(err, msg)(ocl_put_error(err, msg, __FILE__, __LINE__))
# define OCL_ERROR(err, msg)(err != CL_SUCCESS ?  OCL_PUT_ERROR(err, msg): 0)
# define OCL_ERROR2(err)(err != CL_SUCCESS ?  OCL_PUT_ERROR(err, NULL): 0)

#endif
