/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:10:41 by egeant            #+#    #+#             */
/*   Updated: 2019/10/11 11:01:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int value, size_t len)
{
	size_t i;

	i = 0;
	if (str == 0)
		return (str);
	while (i < len)
	{
		*(unsigned char*)(str + i) = (unsigned char)value;
		i++;
	}
	return (str);
}
