/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 10:37:59 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/14 09:40:58 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_n_digits(int n)
{
	size_t	k;

	k = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		k++;
	while (n)
	{
		n /= 10;
		k++;
	}
	return (k);
}

static int	ft_is_minint(int *n)
{
	if (*n == -2147483648)
	{
		*n /= 10;
		return (1);
	}
	return (0);
}

char	*ft_itoa(int n)
{
	size_t	len_s;
	char	*str_nbr;

	len_s = ft_n_digits(n);
	str_nbr = (char *) ft_calloc(len_s + 1, sizeof(char));
	if (str_nbr == NULL)
		return (NULL);
	str_nbr[len_s--] = '\0';
	if (ft_is_minint(&n))
		str_nbr[len_s--] = '8';
	if (n < 0)
	{
		str_nbr[0] = '-';
		n *= -1;
	}
	if (!n)
		str_nbr[len_s] = '0';
	while (n)
	{
		str_nbr[len_s--] = n % 10 + 48;
		n /= 10;
	}
	return (str_nbr);
}
