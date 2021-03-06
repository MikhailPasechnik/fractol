/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlowcase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 21:41:46 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:14:23 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strlowcase(char *str)
{
	char *s;

	s = str;
	while (*str != '\0')
	{
		if (FT_ISUPPER(*str))
		{
			*str = *str + 32;
		}
		str++;
	}
	return (s);
}
