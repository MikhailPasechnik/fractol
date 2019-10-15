#include "fractol.h"

cl_uchar4   parse_pnt(char *str)
{
    size_t      len;
    cl_uchar4   pnt;
    char        **split;

    pnt.x = 0;
    pnt.y = 0;
    pnt.z = 0;
    pnt.w = 0;
    if (!(split = ft_strsplit(str, ' ')))
        return (pnt);
    len = tab_len(split);
    pnt.x = len > 0 ? ft_atoi(split[0]) : 0;
    pnt.y = len > 1 ? ft_atoi(split[1]) : 0;
    pnt.z = len > 2 ? ft_atoi(split[2]) : 0;
    pnt.w = len > 3 ? ft_atoi(split[3]) : 0;
    tab_free(split);
    return (pnt);
}

cl_uchar4    *gradient_from_str(char *gradient)
{
    size_t      i;
    size_t      len;
    cl_uchar4   *g;
    char        **split;

    if (!(split = ft_strsplit(gradient, ',')))
        return NULL;
    len = tab_len(split);
    if (len < 2 || !(g = ft_memalloc(sizeof(*g) * len))) {
        return (tab_free(split));
    }
    i = 0;
    while (i < len)
    {
        g[i] = parse_pnt(split[i]);
        if (i == 0)
            g[i].w = 0;
        else if (i == len -1)
            g[i].w = 100;
        i++;
    }
    return (g);
}
