/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 08:59:20 by bnesoi            #+#    #+#             */
/*   Updated: 2019/10/18 09:07:34 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static cl_uchar4	parse_pnt(char *str)
{
	size_t		len;
	cl_uchar4	pnt;
	char		**split;

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

inline void			gradient_add(t_gradient **list, t_gradient *g)
{
	if (g && list)
	{
		while (g->next)
			g = g->next;
		g->next = *list;
		*list = g;
	}
}

t_gradient			*gradients_from_str(char *str)
{
	t_gradient	*list;
	t_gradient	*g;
	char		**split;
	size_t		i;

	list = NULL;
	if ((split = ft_strsplit(str, '\n')) == NULL)
		return (NULL);
	i = 0;
	while (split[i])
	{
		if ((g = gradient_from_str(split[i])) == NULL)
		{
			ft_putstr_fd("Failed to add gradient: ", 2);
			ft_putendl_fd(split[i], 2);
			i++;
			continue ;
		}
		gradient_add(&list, g);
		i++;
	}
	tab_free(split);
	gradient_list_reverse(&list);
	return (list);
}

t_gradient			*gradient_from_str(char *str)
{
	size_t		i;
	size_t		len;
	t_gradient	*g;
	char		**split;

	if (!(g = ft_memalloc(sizeof(t_gradient))))
		return (NULL);
	ft_bzero(g, sizeof(t_gradient));
	if (!(split = ft_strsplit(str, ',')))
		return (free_gradient(&g));
	len = tab_len(split);
	if (len < 2 || !(g->data = ft_memalloc(sizeof(*g->data) * len)))
	{
		free_gradient(&g);
		return (tab_free(split));
	}
	g->len = len;
	i = 0;
	while (i < len)
	{
		g->data[i] = parse_pnt(split[i]);
		i++;
	}
	tab_free(split);
	return (g);
}
