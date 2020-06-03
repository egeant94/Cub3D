/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 10:40:41 by user42            #+#    #+#             */
/*   Updated: 2020/06/03 14:48:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycasterflat.h"

int			create_trgb(int t, int r, int g, int b)
{
	return (b << 24 | g << 16 | r << 8 | t);
}

int			get_t(int trgb)
{
	return (trgb & 0xFF);
}

int			get_r(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int			get_g(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int			get_b(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}
