/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 23:22:25 by ggiannit          #+#    #+#             */
/*   Updated: 2022/10/10 16:18:32 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_size_word(char const *s, char c, size_t k)
{
	size_t	len;

	len = 0;
	while (s[k + len] != c && s[k + len] != '\0')
		len++;
	return (len);
}

size_t	ft_count_words(char const *s, char c)
{
	size_t	k;
	size_t	words;
	size_t	hold;

	k = 0;
	words = 1;
	hold = 1;
	while (s[k] != '\0')
	{
		if (hold && s[k] == c)
		{
			hold = 0;
			words++;
		}
		else if (s[k] != c)
			hold = 1;
		k++;
	}
	if (hold == 0)
		words--;
	return (words + 1);
}

char	**ft_split(char const *s, char c)
{
	char	**str_matx;
	size_t	k;
	size_t	nbr_str;
	size_t	w_size;

	k = 0;
	nbr_str = 0;
	w_size = 0;
	str_matx = (char **) ft_calloc(ft_count_words(s, c), sizeof(char *));
	if (!str_matx || !s)
		return (NULL);
	while (s[k] != '\0')
	{
		if (s[k] == c)
			k++;
		else
		{
			w_size = ft_size_word(s, c, k);
			str_matx[nbr_str++] = ft_substr(s, k, w_size);
			k += w_size;
		}
	}
	str_matx[nbr_str] = NULL;
	return (str_matx);
}
