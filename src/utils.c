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

size_t			tab_len(char **tab)
{
	size_t len;

	len = 0;
	while (tab && tab[len])
	{
		len++;
	}
	return (len);
}

void            *tab_free(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
        free(tab[i++]);
    free(tab);
    return (NULL);
}

static void		set_fractal(const char *name, const char *src, t_renderer *ren)
{
	ren->kernel_name = ft_strdup(name);
	ren->src = ft_strsplit_any(src, " \n");
	ren->src_count = tab_len(ren->src);
}

int				pick_fractal(const char *name, t_renderer *ren)
{
	if (ft_strcmp(name, MANDELBROT) == 0)
		set_fractal(MANDELBROT, MANDELBROT_SRC, ren);
	else if (ft_strcmp(name, JULIA) == 0)
		set_fractal(JULIA, JULIA_SRC, ren);
	else if (ft_strcmp(name, BURNING_SHIP) == 0)
		set_fractal(BURNING_SHIP, BURNING_SHIP_SRC, ren);
	else
		return (0);
	return (ren->kernel_name && ren->src && ren->src_count);
}

