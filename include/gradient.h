#ifndef GRADIENT_H
#define GRADIENT_H

#include "fractol.h"

typedef struct  s_gradient t_gradient;

typedef struct  s_gradient
{
    cl_uchar4   *data;
    cl_uint     len;
    t_gradient  *head;
    t_gradient  *next;
}               t_gradient;

void            gradient_add(t_gradient **list, cl_uchar4 *data, cl_uint len);
t_gradient      *gradient_from_str(char *str);
void            *free_gradient_list(t_gradient *list);


#endif
