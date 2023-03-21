/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_x.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:55:30 by ggiannit          #+#    #+#             */
/*   Updated: 2022/10/27 12:37:23 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_lutoa_x(t_varpc *svar, unsigned int x_var, size_t x_orig_size)
{
	int		c;
	char	*lutoax;

	lutoax = (char *) malloc(x_orig_size + 1 * sizeof(char));
	lutoax[x_orig_size] = '\0';
	if (!lutoax)
		return (0);
	if (!x_var && svar->prec == 0)
		lutoax[0] = '\0';
	else if (!x_var)
		lutoax[0] = '0';
	else
	{
		while (x_orig_size--)
		{
			c = x_var % 16;
			x_var /= 16;
			if (svar->ascii == 'x')
				lutoax[x_orig_size] = "0123456789abcdef"[c];
			else
				lutoax[x_orig_size] = "0123456789ABCDEF"[c];
		}
	}
	return (lutoax);
}

void	ft_fill_x_0(t_varpc *svar, char *x_conv, char *x, ssize_t x_orig_size)
{
	ssize_t	k;
	ssize_t	s_hold;

	k = 0;
	s_hold = x_orig_size;
	if (svar->flag_sharp && *x_conv != '0')
	{
		x[k++] = '0';
		if (svar->ascii == 'x')
			x[k++] = 'x';
		else
			x[k++] = 'X';
	}
	while (svar->prec-- > x_orig_size)
		x[k++] = '0';
	if (!(*x_conv == '0' && s_hold == 0))
	{
		ft_strlcpy_x(svar, &x[k], x_conv, x_orig_size);
		k += x_orig_size;
	}
	while (svar->length > (size_t) k)
		x[k++] = ' ';
}

void	ft_fill_x_1(t_varpc *svar, char *x_conv,
		char *x, ssize_t x_orig_size)
{
	ssize_t	k;
	ssize_t	s_hold;
	ssize_t	set;

	k = 0;
	set = 0;
	s_hold = x_orig_size;
	while (svar->prec - set > x_orig_size)
		set++;
	if (svar->flag_sharp && *x_conv != '0')
		set += 2;
	while ((ssize_t) svar->length-- > x_orig_size + set)
		x[k++] = ' ';
	if (svar->flag_sharp && *x_conv != '0')
	{
		x[k++] = '0';
		if (svar->ascii == 'x')
			x[k++] = 'x';
		else
			x[k++] = 'X';
	}
	while (svar->prec-- > x_orig_size)
		x[k++] = '0';
	if (!(*x_conv == '0' && s_hold == 0))
		ft_strlcpy_x(svar, &x[k], x_conv, x_orig_size);
}

void	ft_adjust_xsize(t_varpc *svar, unsigned int x_var, size_t *x_size)
{
	if (svar->prec > (ssize_t)(*x_size))
		*x_size = (ssize_t) svar->prec;
	if (svar->flag_sharp && x_var != 0)
		*x_size += 2;
	if (svar->length > *x_size)
		*x_size = svar->length;
}

char	*ft_prepare_x(t_varpc *svar, unsigned int x_var)
{
	char	*x;
	char	*x_conv;
	size_t	x_size;
	size_t	x_orig_size;

	if (!ft_checkconflict_id(svar))
		return (0);
	x_size = ft_get_x_size(x_var);
	x_conv = ft_lutoa_x(svar, x_var, x_size);
	if (x_conv[0] == '\0')
		x_size--;
	x_orig_size = ft_strlen(x_conv);
	ft_adjust_xsize(svar, x_var, &x_size);
	x = (char *) malloc((x_size + 1) * sizeof(char));
	if (!x)
		return (0);
	x[x_size] = '\0';
	if (svar->flag_dash)
		ft_fill_x_0(svar, x_conv, x, x_orig_size);
	else
		ft_fill_x_1(svar, x_conv, x, x_orig_size);
	x = ft_x_handle_zero(svar, x, x_size, x_orig_size);
	free(x_conv);
	return (x);
}
