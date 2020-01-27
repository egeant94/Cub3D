/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeant <egeant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:53:45 by egeant            #+#    #+#             */
/*   Updated: 2019/10/18 14:42:50 by egeant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, void const *src, size_t size)
{
	size_t				i;
	unsigned char		*cdst;
	unsigned char const	*csrc;

	i = 0;
	cdst = dst;
	csrc = src;
	if (src == 0)
		return (dst);
	if (dst == 0)
		return (0);
	while (i < size)
	{
		cdst[i] = csrc[i];
		i++;
	}
	return (dst);
}
