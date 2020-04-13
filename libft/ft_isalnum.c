/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeant <egeant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 10:53:16 by egeant            #+#    #+#             */
/*   Updated: 2019/10/09 11:02:27 by egeant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z')
	|| (c >= 'a' && c <= 'z')
	|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}