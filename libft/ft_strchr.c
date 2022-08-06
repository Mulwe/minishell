/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 03:27:33 by joctopus          #+#    #+#             */
/*   Updated: 2021/04/26 19:36:08 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * 	? ft_strchr(char s, int c) 
 * 	funcion locates the first occurance of c (converted to a char)
 *  in the string pointed by s.
 * 	The terminating null character is considered to be part of the string;
 * 	therefore if c is `\0', the functions locate the terminating `\0'.
 **/

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str != (unsigned char)c)
		if (*str++ == '\0')
			return (NULL);
	return (str);
}
