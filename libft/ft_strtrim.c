/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeant <egeant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:06:56 by marvin            #+#    #+#             */
/*   Updated: 2019/10/18 11:10:41 by egeant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_is_set(char c, char const *set)
{
	int i;

	i = 0;
	if (set == 0)
		return (0);
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char		*ft_strallocim(char const *s1, char const *set, int *i, int *j)
{
	char	*result;

	while (s1[*i] != '\0' && ft_is_set(s1[*i], set))
		(*i)++;
	*j = ft_strlen(s1) - 1;
	while ((*j) >= 0 && ft_is_set(s1[*j], set))
		(*j)--;
	if (*j - *i >= 0)
		result = malloc(*j - *i + 1 + 1);
	else
		result = malloc(1);
	return (result);
}

static void		ft_writestrim(char const *s1, char *result, int i, int j)
{
	int k;

	k = 0;
	while (i <= j)
	{
		result[k] = s1[i];
		i++;
		k++;
	}
	result[k] = '\0';
}

char			*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	if (s1 == 0)
	{
		result = malloc(1);
		i = 1;
	}
	else
		result = ft_strallocim(s1, set, &i, &j);
	if (result == 0)
		return (0);
	ft_writestrim(s1, result, i, j);
	return (result);
}
