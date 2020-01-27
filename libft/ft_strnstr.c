/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeant <egeant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:33:34 by egeant            #+#    #+#             */
/*   Updated: 2019/10/16 13:31:59 by egeant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(char const *haystack, char const *needle, size_t len)
{
	size_t i;
	size_t j;
	size_t k;

	if (needle == 0 || *needle == 0)
		return ((char *)haystack);
	if (len == 0)
		return (0);
	i = 0;
	while (i < len && haystack[i] != '\0')
	{
		j = 0;
		k = i;
		while (haystack[k] == needle[j] && k < len)
		{
			if (j + 1 == ft_strlen(needle))
				return ((char *)haystack + i);
			j++;
			k++;
		}
		i++;
	}
	return (0);
}
