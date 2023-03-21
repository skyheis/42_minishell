/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lutoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 10:37:59 by ggiannit          #+#    #+#             */
/*   Updated: 2022/10/27 12:57:27 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

size_t	ft_lu_digits(long unsigned int n)
{
	size_t	k;

	k = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		k++;
	}
	return (k);
}

char	*ft_lutoa(long unsigned int n)
{
	ssize_t	len_s;
	char	*str_nbr;

	len_s = ft_lu_digits(n);
	str_nbr = (char *) malloc((len_s + 1) * sizeof(char));
	if (str_nbr == NULL)
		return (NULL);
	str_nbr[len_s--] = '\0';
	if (!n)
		str_nbr[len_s] = '0';
	while (n)
	{
		str_nbr[len_s--] = n % 10 + 48;
		n /= 10;
	}
	return (str_nbr);
}

size_t	ft_strlcpy_idu(t_varpc *svar, char *dst, const char *src, size_t size)
{
	size_t	k;

	if (svar->prec == 0 && src[0] == '0')
	{
		dst[svar->length] = '\0';
		return (0);
	}
	k = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (k < size - 1 && src[k] != '\0')
	{
		dst[k] = src[k];
		k++;
	}
	dst[k] = '\0';
	return (ft_strlen(src));
}

size_t	ft_strlcpy_x(t_varpc *svar, char *dst, const char *src, size_t size)
{
	size_t	k;

	(void)svar->ascii;
	k = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (k < size && src[k] != '\0')
	{
		dst[k] = src[k];
		k++;
	}
	dst[k] = '\0';
	return (ft_strlen(src));
}
