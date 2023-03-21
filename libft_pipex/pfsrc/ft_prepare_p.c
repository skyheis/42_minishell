/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 00:25:14 by ggiannit          #+#    #+#             */
/*   Updated: 2022/10/25 21:15:10 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_fill_p_1(t_varpc *svar, uintptr_t p_conv, char *p, size_t p_size)
{
	size_t	i;
	size_t	c;

	i = p_size - 2;
	while (svar->length-- > p_size)
		*p++ = ' ';
	*p++ = '0';
	*p++ = 'x';
	while (i)
	{
		c = p_conv % 16;
		p_conv /= 16;
		p[i - 1] = "0123456789abcdef"[c];
		i--;
	}
}

void	ft_fill_p_0(t_varpc *svar, uintptr_t p_conv, char *p, size_t p_size)
{
	size_t	i;
	size_t	c;

	i = p_size - 2;
	*p++ = '0';
	*p++ = 'x';
	while (i)
	{
		c = p_conv % 16;
		p_conv /= 16;
		p[i - 1] = "0123456789abcdef"[c];
		i--;
	}
	i = p_size - 2;
	while (svar->length-- > p_size)
		p[i++] = ' ';
}

size_t	ft_size_for_p(uintptr_t p_conv)
{
	size_t	k;

	k = 2;
	while (p_conv)
	{
		p_conv /= 16;
		k++;
	}
	return (k);
}

char	*ft_prepare_p(t_varpc *svar, void *p_var)
{
	uintptr_t	p_conv;
	char		*p;
	size_t		p_size;

	if (svar->prec != -1 || svar->flag_zero || svar->flag_plus
		|| svar->flag_sharp || svar->flag_32)
		return (0);
	p_conv = (uintptr_t)p_var;
	p_size = ft_size_for_p(p_conv);
	if (svar->length > p_size)
		p_size = svar->length;
	p = (char *) malloc((p_size + 1) * sizeof(char));
	if (!p)
		return (0);
	p[p_size] = '\0';
	p_size = ft_size_for_p(p_conv);
	if (svar->flag_dash)
		ft_fill_p_0(svar, p_conv, p, p_size);
	else
		ft_fill_p_1(svar, p_conv, p, p_size);
	return (p);
}
