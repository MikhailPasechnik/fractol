#ifndef UTILS_H
# define UTILS_H

int	iteration_to_color(double iteration, double iteration_max, __global uchar4 *gradient, uint gradient_len);
double smooth_iteration(double iterations, double r, double i);

#endif
