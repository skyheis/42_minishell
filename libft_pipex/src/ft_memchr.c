/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:46:33 by ggiannit          #+#    #+#             */
/*   Updated: 2022/10/07 16:33:24 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	k;
	char	*t;

	k = 0;
	t = (void *)s;
	while (k < n)
	{
		if ((char)c == t[k])
			return (&t[k]);
		k++;
	}
	return (NULL);
}
