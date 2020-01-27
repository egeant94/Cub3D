/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:05:27 by marvin            #+#    #+#             */
/*   Updated: 2019/10/17 14:58:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*result;

	if (s == 0)
	{
		if (!(result = malloc(1)))
			return (0);
		result[0] = 0;
		return (result);
	}
	if (f == 0)
		return (ft_strdup(s));
	if (!(result = malloc(ft_strlen(s) + 1)))
		return (0);
	i = 0;
	while (s != 0 && s[i] != '\0')
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
