/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:38:02 by ggiannit          #+#    #+#             */
/*   Updated: 2022/10/06 21:04:28 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	k;

	k = 0;
	while (s[k] != '\0')
	{
		if (s[k] == c)
			return ((char *)&s[k]);
		k++;
	}
	if (s[k] == c)
		return ((char *)&s[k]);
	return (NULL);
}
