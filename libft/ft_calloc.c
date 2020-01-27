/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeant <egeant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:42:31 by egeant            #+#    #+#             */
/*   Updated: 2019/10/18 14:45:18 by egeant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t len, size_t size)
{
	size_t			i;
	unsigned char	*memad;

	if (!(memad = malloc(len * size)))
		return (0);
	i = 0;
	while (i < len * size)
	{
		memad[i] = 0;
		i++;
	}
	return ((void *)memad);
}
