/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 12:57:02 by ggiannit          #+#    #+#             */
/*   Updated: 2022/10/09 13:07:57 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_str;
	size_t	k;

	if (!s)
		return (NULL);
	k = 0;
	new_str = (char *) malloc((ft_strlen(s) + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	while (s[k] != '\0')
	{
		new_str[k] = (*f)(k, s[k]);
		k++;
	}
	new_str[k] = '\0';
	return (new_str);
}
