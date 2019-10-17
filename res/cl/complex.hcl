#ifndef COMPLEX_H
# define COMPLEX_H

typedef struct	s_complex
{
	double	r;
	double	i;
}				t_complex;

t_complex	c_add(t_complex a, t_complex b);
t_complex	c_sub(t_complex a, t_complex b);
t_complex	c_mul(t_complex a, t_complex b);
t_complex	c_div(t_complex a, t_complex b);
t_complex	c_abs(t_complex a);

#endif
