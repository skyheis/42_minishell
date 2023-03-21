/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:25:20 by ggiannit          #+#    #+#             */
/*   Updated: 2022/10/09 23:04:22 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			k;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (!dest && !src)
		return (dest);
	if (dest <= src)
	{
		k = 0;
		while (k < n)
		{
			d[k] = s[k];
			k++;
		}
	}
	else
	{
		k = n;
		while (k--)
			d[k] = s[k];
	}
	return (dest);
}

/*void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	k;

	if (!dest && !src)
		return (dest);
	if (dest <= src)
	{
		k = 0;
		while (k < n)
		{
			((unsigned char *)dest)[k] = ((unsigned char *)src)[k];
			k++;
		}
	}
	else
	{
		k = n;
		while (k--)
			((unsigned char *)dest)[k] = ((unsigned char *)src)[k];
	}
	return (dest);
}*/
