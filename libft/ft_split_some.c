/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_some.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 06:46:08 by joctopus          #+#    #+#             */
/*   Updated: 2022/02/07 19:50:03 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	number_str(char *s, char c)
{
	int		n[2];
	char	quote;

	n[0] = -1;
	n[1] = 1;
	while (s[++n[0]])
	{
		if (s[n[0]] == '\\' && (s[n[0] + 1] == '\'' || s[n[0] + 1] == '"' || \
								s[n[0] + 1] == '\\' || s[n[0] + 1] == c))
			n[0]++;
		else if (s[n[0]] == c)
			n[1]++;
		else if (s[n[0]] && (s[n[0]] == '"' || s[n[0]] == '\''))
		{
			quote = s[n[0]++];
			while (s[n[0]] && s[n[0]] != quote)
			{
				if (s[n[0]] == '\\' && \
				(s[n[0] + 1] == quote || s[n[0] + 1] == '\\') && quote == '"')
					n[0]++;
				n[0]++;
			}
		}
	}
	return (n[1]);
}

static int	set_strlen(char *s, char c)
{
	char	quote;
	int		len;

	len = -1;
	while (s[++len] && s[len] != c)
	{
		if (s[len] == '\\' && (s[len + 1] == '\'' || s[len + 1] == '"' || \
		s[len + 1] == '\\' || s[len + 1] == c))
			len++;
		else if (s[len] == '"' || s[len] == '\'')
		{
			quote = s[len++];
			while (s[len] && s[len] != quote)
			{
				if (s[len] == '\\' && \
				(s[len + 1] == quote || s[len + 1] == '\\') && quote == '"')
					len++;
				len++;
			}
		}
	}
	return (len);
}

static void	set_mtrx(char **mtrx, char *s, char c, int n)
{
	int	i;
	int	len;

	i = 0;
	while (i < n)
	{
		len = set_strlen(s, c);
		mtrx[i] = ft_substr(s, 0, len);
		s += len + 1;
		i++;
	}
}

char	**ft_split_some(char *s, char c)
{
	int		n;
	char	**mtrx;

	if (!s)
		return (NULL);
	n = number_str(s, c);
	mtrx = (char **)ft_calloc(sizeof(char *), n + 1);
	if (!mtrx)
		return (NULL);
	set_mtrx(mtrx, s, c, n);
	return (mtrx);
}
