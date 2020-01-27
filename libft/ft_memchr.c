/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeant <egeant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 10:30:30 by egeant            #+#    #+#             */
/*   Updated: 2019/10/15 13:55:27 by egeant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void const *str, int c, size_t size)
{
	size_t i;

	if (str == 0)
		return (0);
	i = 0;
	while (i < size)
	{
		if (*(unsigned char*)(str + i) == (unsigned char)c)
			return ((void *)str + i);
		i++;
	}
	return (0);
}
