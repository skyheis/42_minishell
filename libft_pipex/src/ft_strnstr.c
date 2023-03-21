/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:01:01 by ggiannit          #+#    #+#             */
/*   Updated: 2022/10/09 23:07:35 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	c;
	size_t	n_len;
	char	*b;

	i = 0;
	b = (char *)big;
	n_len = ft_strlen(little);
	if (n_len == 0 || big == little)
		return (b);
	if (len == 0)
		return (0);
	while (b[i] != '\0' && i < len)
	{
		c = 0;
		while (b[i + c] != '\0' && little[c] != '\0'
			&& b[i + c] == little[c] && i + c < len)
			c++;
		if (c == n_len)
			return (b + i);
		i++;
	}
	return (0);
}
