/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:00:08 by egeant            #+#    #+#             */
/*   Updated: 2019/10/17 10:40:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(char const *str)
{
	int i;
	int result;
	int signe;

	if (str == 0)
		return (0);
	i = 0;
	signe = 1;
	while ((str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		&& str[i] != '\0')
		i++;
	if (str[i] == '-')
		signe = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = str[i] - '0' + result * 10;
		i++;
	}
	return (result * signe);
}
