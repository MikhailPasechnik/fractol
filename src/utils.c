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
