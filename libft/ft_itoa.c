/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeant <egeant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 14:30:01 by marvin            #+#    #+#             */
/*   Updated: 2019/10/18 14:44:38 by egeant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_integer_len(int n)
{
	int len;

	if (n < 0)
		len = 2;
	else
		len = 1;
	while (n > 9 || n < -9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	long int		ln;
	char			*result;
	int				integer_len;

	integer_len = ft_integer_len(n);
	if (!(result = malloc(integer_len + 1)))
		return (0);
	ln = n;
	if (n < 0)
	{
		ln = -ln;
		result[0] = '-';
	}
	result[integer_len] = '\0';
	integer_len--;
	while (integer_len >= 0)
	{
		if (result[0] == '-' && integer_len == 0)
			break ;
		result[integer_len] = ln % 10 + '0';
		ln /= 10;
		integer_len--;
	}
	return (result);
}
