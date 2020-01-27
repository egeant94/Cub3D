/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeant <egeant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 10:15:46 by egeant            #+#    #+#             */
/*   Updated: 2019/10/14 14:38:57 by egeant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_isvalid(char const *s, unsigned int start)
{
	char *result;

	if (start >= ft_strlen(s))
	{
		if (!(result = malloc(1)))
			return (0);
		result[0] = 0;
		return (result);
	}
	return (0);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*result;
	size_t	final_len;

	if (s == 0)
		return (0);
	if ((result = ft_isvalid(s, start)))
		return (result);
	final_len = 0;
	i = 0;
	while (s[start + i] != '\0' && i < len)
	{
		final_len++;
		i++;
	}
	if (!(result = malloc(final_len + 1)))
		return (0);
	i = 0;
	while (i < final_len)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
