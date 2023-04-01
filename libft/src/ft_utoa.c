/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:46:56 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/01 17:03:46 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_utoa(unsigned int nb)
{
	char			*str;
	unsigned int	n;
	size_t			len;

	n = nb;
	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	if (!nb)
		len++;
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (0);
	if (!nb)
		str[0] = '0';
	str[len] = 0;
	while (nb && len--)
	{
		str[len] = nb % 10 + '0';
		nb /= 10;
	}
	return (str);
}
