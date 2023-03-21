/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 21:04:44 by ggiannit          #+#    #+#             */
/*   Updated: 2022/10/08 11:22:52 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	k;

	k = ft_strlen(s);
	while (k > 0)
	{
		if (s[k] == c)
			return ((char *)&s[k]);
		k--;
	}
	if (s[0] == c)
		return ((char *)&s[0]);
	return (NULL);
}
