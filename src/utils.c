/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:55:25 by bnesoi            #+#    #+#             */
/*   Updated: 2019/06/21 12:52:38 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

size_t			tab_len(const char **tab)
{
	size_t len;

	len = 0;
	while (tab && tab[len])
	{
		len++;
	}
	return (len);
}

static void		set_fractal(const char *name, const char *src, t_renderer *ren)
{
	ren->kernel_name = ft_strnew(ft_strlen(name));
	ren->src = ft_strsplit(src, ' ');
	ren->src_count = tab_len((const char **)ren->src);
}

int				pick_fractal(const char *name, t_renderer *ren)
{
	if (ft_strcmp(name, MANDELBROT) == 0)
		set_fractal(MANDELBROT, MANDELBROT_SRC, ren);
	else if (ft_strcmp(name, JULIA) == 0)
		set_fractal(JULIA, JULIA_SRC, ren);
	else
		return (0);
	return (ren->kernel_name && ren->src && ren->src_count);
}
