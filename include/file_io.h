/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_io.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 09:11:49 by bnesoi            #+#    #+#             */
/*   Updated: 2019/10/18 09:13:10 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_IO_H
# define FILE_IO_H

# include <fcntl.h>
# include <errno.h>
# include "libft.h"
# include "ft_printf.h"

int		fio_open_fd(const char *file_name);
char	*fio_read_file(const char *file_name, size_t *size);
int		fio_read_files(const char **file_names, size_t count,
	char ***content, size_t **size);
int		save_image(const char *file_name,
	unsigned int *data, size_t w, size_t h);

#endif
