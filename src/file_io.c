#include "file_io.h"

int 		fio_open_fd(const char *file_name)
{
    int		fd;

    if ((fd = open(file_name, O_RDONLY)) < 0)
        return (0);
    if (read(fd, NULL, 0) != 0)
    {
        close(fd);
        return (0);
    }
    return (fd);
}

char 	*fio_read_file(const char *file_name, size_t *size)
{
    int		fd;
    int		rd;
    char 	buff[1024 + 1];
    char 	*str;
    char 	*joined;

    if (!(fd = fio_open_fd(file_name)))
        return (NULL);
    if (size)
        *size = 0;
    str = NULL;
    while ((rd = read(fd, buff, 1024)))
    {
        if (size)
            *size += rd;
        buff[rd] = '\0';
        joined = ft_strjoin(str ? str : "", buff);
        if (str)
            ft_strdel(&str);
        if ((str = joined) == NULL)
            break ;
    }
    close(fd);
    return (str);
}

int		fio_read_files(const char **file_names, size_t count,
                          char ***content, size_t **size)
{
    size_t	i;

    if (!(*content = malloc(sizeof(**content) * count)) ||
        !(*size = malloc(sizeof(**size) * count)))
    {
        *content ? free(*content) : 0;
        return 0;
    }
    i = 0;
    while (i < count)
    {
        if (((*content)[i] = fio_read_file(file_names[i], &(*size)[i])) == NULL)
        {
            ft_putstr_fd("Failed to read file: ", 2);
            ft_putendl_fd(file_names[i], 2);
            while(i--)
                free((*content)[i]);
            free(*content);
            free(*size);
            break ;
        }
        i++;
    }
    return (i == count);
}