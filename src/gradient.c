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

void        *free_gradient(t_gradient *g)
{
    if (!g)
        return (NULL);
    free(g->data);
    free(g);
    return (NULL);
}

void        *free_gradient_list(t_gradient *list)
{
    t_gradient *next;

    while (list)
    {
        next = list->next;
        free_gradient(list);
        list = next;
    }
}

t_gradient    *gradient_from_str(char *str)
{
    size_t      i;
    size_t      len;
    t_gradient  *g;
    char        **split;

    if (!(g = ft_memalloc(sizeof(t_gradient))))
        return NULL;
    ft_bzero(g, sizeof(t_gradient));
    if (!(split = ft_strsplit(str, ',')))
        return (free_gradient(g));
    len = tab_len(split);
    if (len < 2 || !(g->data = ft_memalloc(sizeof(*g->data) * len))) {
        free_gradient(g);
        return (tab_free(split));
    }
    g->len = len;
    i = 0;
    while (i < len)
    {
        g->data[i] = parse_pnt(split[i]);
        if (i == 0)
            g->data[i].w = 0;
        else if (i == len -1)
            g->data[i].w = 100;
        i++;
    }
    return (g);
}
