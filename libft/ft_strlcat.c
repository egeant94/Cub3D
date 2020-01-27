/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeant <egeant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:59:16 by egeant            #+#    #+#             */
/*   Updated: 2019/10/16 11:11:40 by egeant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, char const *src, size_t dst_size)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;

	i = 0;
	dst_len = ft_strlen(dst);
	if (dst_len > dst_size || dst == 0)
		return (dst_size + ft_strlen(src));
	if (src == 0)
	{
		dst[dst_len] = '\0';
		return (dst_len);
	}
	i = dst_len;
	j = 0;
	while (i < dst_size - 1 && src[j] != '\0')
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst_len + ft_strlen(src));
}
