/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 08:59:46 by bnesoi            #+#    #+#             */
/*   Updated: 2019/10/18 09:09:46 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"
#include "file_io.h"

cl_program		ocl_create_program(cl_context ctx,
	const char **file_names, size_t count)
{
	cl_program	program;
	char		**content;
	cl_int		err;
	size_t		*size;

	if (!(fio_read_files(file_names, count, &content, &size)))
		return (NULL);
	program = clCreateProgramWithSource(ctx, count,
		(const char **)content, size, &err);
	while (count--)
		free(content[count]);
	free(content);
	free(size);
	if (OCL_ERROR(err, "Couldn't create the program"))
		return (NULL);
	return (program);
}
