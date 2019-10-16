#ifndef UTILS_H
# define UTILS_H

typedef struct  s_frgb
{
	float r;
	float g;
	float b;
}               t_frgb;
int	iteration_to_color(double iteration, double iteration_max, __global uchar4 *gradient, uint gradient_len);

#endif
