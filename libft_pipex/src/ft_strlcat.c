/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:36:01 by ggiannit          #+#    #+#             */
/*   Updated: 2022/10/06 16:54:37 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	k;
	size_t	j;

	len_dst = ft_strlen(dst);
	k = len_dst;
	j = 0;
	if (size <= len_dst)
		return (size + ft_strlen(src));
	while (j < (size - len_dst - 1) && src[j] != '\0')
	{
		dst[k] = src[j];
		k++;
		j++;
	}
	dst[k] = '\0';
	return (len_dst + ft_strlen(src));
}
