/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 09:16:27 by bnesoi            #+#    #+#             */
/*   Updated: 2019/10/18 09:17:49 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRADIENT_H
# define GRADIENT_H

# include "fractol.h"

typedef struct	s_gradient
{
	cl_uchar4			*data;
	cl_uint				len;
	struct s_gradient	*next;
}				t_gradient;

void			gradient_add(t_gradient **list, t_gradient *g);
t_gradient		*gradient_from_str(char *str);
t_gradient		*gradients_from_str(char *str);
void			*free_gradient_list(t_gradient **list);
void			gradient_list_reverse(t_gradient **list);
void			*free_gradient(t_gradient **g);

#endif
