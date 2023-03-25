/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:07:12 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/25 14:11:39 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t	k;
	char	*sub_str;

	k = 0;
	if (!str)
		return (NULL);
	if (start >= ft_strlen(str))
		len = 0;
	sub_str = (char *) ft_calloc((len + 1), sizeof(char));
	if (sub_str == NULL)
		return (NULL);

	while (str && str[start + k] && k < len)
	{
		sub_str[k] = str[start + k];
		k++;
	}
	return (sub_str);
}

/*ft_strlcpy(sub_str, &s[start], len + 1);*/
/*#include <stdio.h>

int	main(void)
{
	printf("%s\n", ft_substr("this is 42", 3, 5));
}*/
