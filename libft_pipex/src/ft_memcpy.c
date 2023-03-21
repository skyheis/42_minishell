/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:00:43 by ggiannit          #+#    #+#             */
/*   Updated: 2022/10/09 23:04:45 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	k;

	k = 0;
	if (!dest && !src)
		return (dest);
	while (k < n)
	{
		((unsigned char *)dest)[k] = ((unsigned char *)src)[k];
		k++;
	}
	return (dest);
}
