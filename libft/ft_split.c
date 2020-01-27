/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeant <egeant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 10:16:23 by egeant            #+#    #+#             */
/*   Updated: 2019/10/22 10:13:27 by egeant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_taballoc(char const *s, char c)
{
	unsigned int	i;
	int				size;
	char			**result;

	i = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	if (i == ft_strlen(s))
		size = 0;
	else
		size = 1;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			size++;
		i++;
	}
	if (!(result = malloc((size + 1) * sizeof(*result))))
		return (0);
	result[size] = 0;
	return (result);
}

static int	ft_stralloc(char **result, char const *s, char c)
{
	int		i;
	int		j;
	int		size;

	i = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	j = 0;
	size = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			size++;
		if ((s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			|| s[i + 1] == '\0')
		{
			if (!(result[j] = malloc(size + 1)))
				return (j);
			result[j][size] = '\0';
			j++;
			size = 0;
		}
		i++;
	}
	return (0);
}

static void	ft_write(char **result, char const *s, char c)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	j = 0;
	k = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			result[j][k] = s[i];
			k++;
		}
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
		{
			j++;
			k = 0;
		}
		i++;
	}
}

static char	**ft_ifnull(void)
{
	char	**result;

	if (!(result = malloc(sizeof(*result))))
		return (0);
	result[0] = 0;
	return (result);
}

char		**ft_split(char const *s, char c)
{
	char	**result;
	int		leak;
	int		i;

	i = 0;
	if (s == 0)
		return (ft_ifnull());
	if (!(result = ft_taballoc(s, c)))
		return (0);
	if ((leak = ft_stralloc(result, s, c)))
	{
		while (i < leak)
		{
			free(result[i]);
			i++;
		}
		free(result);
		return (0);
	}
	ft_write(result, s, c);
	return (result);
}
