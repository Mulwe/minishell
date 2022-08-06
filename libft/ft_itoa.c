/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:09:51 by mjerrica          #+#    #+#             */
/*   Updated: 2021/10/22 16:31:17 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbr_size(long n)
{
	int	size;

	if (n < 0)
	{
		n *= -1;
		size = 2;
	}
	else
		size = 1;
	while (n > 9)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static void	ft_convint(long num, char *res, int nbr_size, int n)
{
	res[nbr_size--] = '\0';
	if (n < 0)
	{
		res[0] = '-';
		num *= -1;
	}
	while (num > 0)
	{
		res[nbr_size--] = (num % 10) + '0';
		num /= 10;
	}
}

char	*ft_itoa(int n)
{
	int		nbr_size;
	long	num;
	char	*res;

	nbr_size = ft_nbr_size(n);
	num = n;
	res = (char *)malloc(sizeof(char) * nbr_size + 1);
	if (!res)
		return (NULL);
	if (n == 0)
	{
		res[0] = '0';
		res[1] = '\0';
		return (res);
	}
	ft_convint(num, res, nbr_size, n);
	return (res);
}
