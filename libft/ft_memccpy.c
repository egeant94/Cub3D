/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeant <egeant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:59:13 by egeant            #+#    #+#             */
/*   Updated: 2019/10/18 14:43:33 by egeant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, void const *src, int c, size_t len)
{
	size_t				i;
	unsigned char		*c_dst;
	unsigned char const	*c_src;

	c_dst = dst;
	c_src = src;
	if (dst == 0 || src == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		c_dst[i] = c_src[i];
		if (c_src[i] == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	return (0);
}
