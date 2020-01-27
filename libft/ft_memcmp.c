/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 10:37:15 by egeant            #+#    #+#             */
/*   Updated: 2019/10/11 11:01:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(void const *str1, void const *str2, size_t size)
{
	size_t				i;
	unsigned char const	*cstr1;
	unsigned char const	*cstr2;

	cstr1 = str1;
	cstr2 = str2;
	if (str1 == 0 && str2 == 0)
		return (0);
	if (str2 == 0)
		return (cstr1[0]);
	if (str1 == 0)
		return (-cstr2[0]);
	i = 0;
	while (i < size)
	{
		if (cstr1[i] != cstr2[i])
			return (cstr1[i] - cstr2[i]);
		i++;
	}
	return (0);
}
