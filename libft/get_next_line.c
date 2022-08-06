/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:36:23 by joctopus          #+#    #+#             */
/*   Updated: 2022/03/10 03:51:44 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#if defined(BUFFER_SIZE)
#else
# define BUFFER_SIZE 1 
#endif

static int	ft_writeline(char **dest, char **src)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while ((*src)[i] != '\n' && (*src)[i] != '\0')
		i++;
	if ((*src)[i] == '\n')
	{
		*dest = ft_substr(*src, 0, i);
		tmp = ft_strdup(*src + (i + 1));
		free(*src);
		*src = tmp;
	}
	else
	{
		*dest = ft_strdup(*src);
		free(*src);
		*src = NULL;
	}
	if ((*src)[i] != '\0')
		return (1);
	return (0);
}

static int	ft_result(long ret, char **save, char **line)
{
	if (ret < 0)
		return (-1);
	else if (ret == 0 && save == NULL)
		return (0);
	return (ft_writeline(line, save));
}

/**
 *  return 
 * 	0: A line has been read
 * 	1: EOF has been reached
 * 	-1: An error happend
 * */

int	get_next_line(int fd, char **line)
{
	long		ret;
	char		*tmp;
	char		buf[BUFFER_SIZE + 1];
	static char	*save;

	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, &buf, BUFFER_SIZE);
		if (ret < 0 || line == NULL)
			return (-1);
		buf[ret] = '\0';
		if (save != NULL)
		{
			tmp = ft_strjoin(save, buf);
			free(save);
			save = tmp;
		}
		else
			save = ft_strdup(buf);
		if (ft_strchr(save, '\n'))
			break ;
	}
	return (ft_result(ret, &save, line));
}
