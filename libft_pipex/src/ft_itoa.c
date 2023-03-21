/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 10:37:59 by ggiannit          #+#    #+#             */
/*   Updated: 2022/10/09 12:29:40 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_n_digits(int n)
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

char	*ft_itoa(int n)
{
	size_t	len_s;
	char	*str_nbr;

	str_nbr = (char *) malloc(((len_s = ft_n_digits(n)) + 1) * sizeof(char));
	if (str_nbr == NULL)
		return (NULL);
	str_nbr[len_s--] = '\0';
	if (n == -2147483648)
	{
		str_nbr[len_s--] = '8';
		n /= 10;
	}
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
