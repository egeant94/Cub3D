/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 10:26:14 by egeant            #+#    #+#             */
/*   Updated: 2020/06/02 11:07:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_freebuffer(char *buff)
{
	if (buff != 0)
	{
		free(buff);
		buff = 0;
	}
	return (-1);
}

static int	ft_nullline(char **line, char *buff)
{
	if ((*line = malloc(1)) == 0)
		return (-1);
	*line[0] = '\0';
	ft_freebuffer(buff);
	return (0);
}

static int	ft_tempfix(char **temp, int i)
{
	char	*t;

	if ((*temp)[i] == '\0')
	{
		free(*temp);
		*temp = 0;
		return (0);
	}
	if (!(t = ft_strdup(*temp + i + 1)))
	{
		free(*temp);
		return (-1);
	}
	free(*temp);
	*temp = t;
	return (1);
}

static int	ft_append(char **temp, char **line, char *buff)
{
	int		i;

	i = 0;
	while ((*temp)[i] != '\n' && (*temp)[i] != '\0')
		i++;
	if (!(*line = malloc(i + 1)))
	{
		free(*temp);
		ft_freebuffer(buff);
		return (-1);
	}
	i = 0;
	while ((*temp)[i] != '\n' && (*temp)[i] != '\0')
	{
		(*line)[i] = (*temp)[i];
		i++;
	}
	(*line)[i] = '\0';
	ft_freebuffer(buff);
	return (ft_tempfix(temp, i));
}

int			get_next_line(int fd, char **line)
{
	static char		*temp;
	char			*buff;
	int				red;

	if (fd < 0 || line == 0 || BUFFER_SIZE < 1)
		return (-1);
	if (!(buff = malloc(BUFFER_SIZE + 1)))
		return (-1);
	if (ft_strchr(temp, '\n'))
		return (ft_append(&temp, line, buff));
	while ((red = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[red] = '\0';
		if (!(temp = ft_strjoinfree(temp, buff)))
			return (ft_freebuffer(buff));
		if (ft_strchr(temp, '\n'))
			break ;
	}
	if (red == -1)
		return (ft_freebuffer(buff));
	if (temp != 0)
		return (ft_append(&temp, line, buff));
	return (ft_nullline(line, buff));
}
