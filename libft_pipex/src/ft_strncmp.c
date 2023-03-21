/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:34:37 by ggiannit          #+#    #+#             */
/*   Updated: 2023/01/03 16:18:26 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	k;

	k = 0;
	if (!s1 || !s2)
		return (2);
	while (k < n && (s1[k] != '\0' || s2[k] != '\0'))
	{
		if (((unsigned char *)s1)[k] < ((unsigned char *)s2)[k])
			return (-1);
		if (((unsigned char *)s1)[k] > ((unsigned char *)s2)[k])
			return (1);
		k++;
	}
	return (0);
}
