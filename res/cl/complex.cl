#include "complex.hcl"

inline t_complex	c_add(t_complex a, t_complex b)
{
	return ((t_complex) {a.r + b.r, a.i + b.i});
}

inline t_complex	c_sub(t_complex a, t_complex b)
{
	return ((t_complex) {a.r - b.r, a.i - b.i});
}

inline t_complex	c_mul(t_complex a, t_complex b)
{
	return ((t_complex) {a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r});
}

inline t_complex	c_div(t_complex a, t_complex b)
{
	return (t_complex) {
			(a.r * b.r + a.i * b.i) / (b.r * b.r + b.i * b.i),
			(a.i * b.r - a.r * b.i) / (b.r * b.r + b.i * b.i)
	};
}

inline t_complex	c_abs(t_complex a)
{
	return ((t_complex) {hypot(a.r, a.i), 0});
}
