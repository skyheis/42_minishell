/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_cs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:33:02 by ggiannit          #+#    #+#             */
/*   Updated: 2022/10/27 10:06:27 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_fill_c(t_varpc *svar, char c_var, char *c, size_t c_size)
{
	c[c_size] = '\0';
	if (svar->flag_dash)
	{
		*c++ = c_var;
		while (c_size-- > 1)
			*c++ = 32;
	}
	else
	{
		c[c_size - 1] = c_var;
		while (*c != c_var)
			*c++ = 32;
	}
}

char	*ft_prepare_c(t_varpc *svar, char c_var)
{
	char	*c;
	size_t	c_size;

	if (svar->prec != -1 || svar->flag_32 || svar->flag_plus
		|| svar->flag_sharp || svar->flag_zero)
		return (0);
	if (svar->length)
		c_size = svar->length;
	else
		c_size = 1;
	c = (char *) malloc((c_size + 1) * sizeof(char));
	if (!c)
		return (0);
	ft_fill_c(svar, c_var, c, c_size);
	return (c);
}

void	ft_fill_s(t_varpc *svar, char *s_var, char *s, size_t s_size)
{
	size_t	s_var_len;

	s_var_len = ft_strlen(s_var);
	s[s_size] = '\0';
	if (svar->flag_dash)
	{
		s_var_len = ft_strlcpy(s, s_var, s_size + 1);
		while (s_var_len < s_size)
			s[s_var_len++] = 32;
	}
	else
	{
		while ((s_size - s_var_len) > 0)
		{
			*s++ = 32;
			s_size--;
		}
		ft_strlcpy(s, s_var, s_var_len + 1);
	}
}

char	*ft_prepare_s(t_varpc *svar, char *s_var)
{
	char	*s;
	size_t	s_size;
	size_t	s_var_orig_len;

	s_var_orig_len = ft_strlen(s_var);
	if (svar->flag_32 || svar->flag_plus
		|| svar->flag_sharp || svar->flag_zero)
		return (0);
	if (svar->prec != -1 && svar->prec < (ssize_t) s_var_orig_len)
		s_var = ft_substr(s_var, 0, svar->prec);
	s_size = ft_strlen(s_var);
	if (s_size < svar->length)
		s_size = svar->length;
	s = (char *) malloc((s_size + 1) * sizeof(char));
	if (!s)
		return (0);
	ft_fill_s(svar, s_var, s, s_size);
	if (svar->prec != -1 && svar->prec < (ssize_t) s_var_orig_len)
		free(s_var);
	return (s);
}
