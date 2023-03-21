/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:07:12 by ggiannit          #+#    #+#             */
/*   Updated: 2022/10/08 18:47:57 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	sub_str = (char *) malloc((len + 1) * sizeof(char));
	if (sub_str == NULL)
		return (NULL);
	ft_strlcpy(sub_str, &s[start], len + 1);
	return (sub_str);
}

/*#include <stdio.h>

int	main(void)
{
	printf("%s\n", ft_substr("this is 42", 3, 5));
}*/
