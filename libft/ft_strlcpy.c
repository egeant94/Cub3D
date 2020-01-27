/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeant <egeant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:42:41 by egeant            #+#    #+#             */
/*   Updated: 2019/10/16 11:34:27 by egeant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dst, char const *src, size_t size)
{
	int i;

	i = 0;
	if (src == 0 || dst == 0)
		return (ft_strlen(src));
	while (src[i] != '\0' && i < (int)size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (size > 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}
