/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:22:43 by joctopus          #+#    #+#             */
/*   Updated: 2021/04/26 19:42:57 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_len(char const *s, size_t len, unsigned int start)
{
	if (len > ft_strlen(s + start))
		return (ft_strlen(s + start));
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		substr = (char *)malloc(sizeof(char));
		if (!substr)
			return (NULL);
		*substr = '\0';
		return (substr);
	}
	len = ft_check_len(s, len, start);
	substr = (char *)malloc(len * sizeof(char) + 1);
	if (!substr)
		return (NULL);
	while (len > 0)
	{
		substr[i++] = s[start++];
		len--;
	}
	substr[i] = '\0';
	return (substr);
}
