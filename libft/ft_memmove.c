/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 10:19:17 by egeant            #+#    #+#             */
/*   Updated: 2019/10/17 11:51:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dst, void const *src, size_t size)
{
	unsigned char		*cdst;
	unsigned char const	*csrc;
	size_t				i;

	cdst = dst;
	csrc = src;
	i = 0;
	if (csrc == 0 || cdst == 0)
		return (0);
	if (csrc == cdst)
		return (dst);
	if (csrc > cdst)
		while (i < size)
		{
			cdst[i] = csrc[i];
			i++;
		}
	else
		while (i < size)
		{
			cdst[size - 1 - i] = csrc[size - 1 - i];
			i++;
		}
	return ((void *)cdst);
}
