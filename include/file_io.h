#ifndef FILE_IO_H
#define FILE_IO_H

# include <fcntl.h>
# include <errno.h>
# include "libft.h"

int 	fio_open_fd(const char *file_name);
char 	*fio_read_file(const char *file_name, size_t *size);
int		fio_read_files(const char **file_names, size_t count,
                          char ***content, size_t **size);
#endif
