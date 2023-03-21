/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_zeros.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:39:14 by ggiannit          #+#    #+#             */
/*   Updated: 2022/10/27 10:03:45 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_idu_handle_zero(t_varpc *svar, char *idu, char itoa_0)
{
	size_t	k;

	k = 0;
	if (svar->flag_zero)
	{
		while (!ft_isdigit(idu[k]))
			idu[k++] = '0';
		if (itoa_0 == '-')
			idu[0] = '-';
		else if (svar->flag_plus)
			idu[0] = '+';
		else if (svar->flag_32)
			idu[0] = ' ';
	}
	return (idu);
}

char	*ft_x_handle_zero(t_varpc *svar, char *x,
		size_t x_size, size_t x_orig_size)
{
	size_t	k;

	k = 0;
	if (svar->flag_zero)
	{
		while (x_size-- - x_orig_size)
			x[k++] = '0';
		if (svar->flag_sharp)
		{
			if (svar->ascii == 'x')
				x[1] = 'x';
			else
				x[1] = 'X';
		}
	}
	return (x);
}

int	ft_get_x_size(unsigned int x_var)
{
	int	k;

	k = 0;
	while (x_var > 0)
	{
		x_var /= 16;
		k++;
	}	
	if (!k)
		return (1);
	return (k);
}

int	ft_putstr_pf_fd(const char *str, int fd)
{
	int	k;
	int	pf;

	k = 0;
	pf = 0;
	while (str[k] != '\0')
	{
		if (str[k] == '%' && str[k + 1] == '%')
		{
			write(fd, "%", 1);
			pf++;
			k += 2;
		}
		else
		{
			write(fd, &str[k++], 1);
			pf++;
		}
	}
	return (pf);
}

int	ft_handle_nil(t_varpc *svar)
{
	int	k;

	k = 0;
	if (svar->prec > 0 && svar->prec < 5)
		return (0);
	while (svar->length-- > 5)
	{
		write(1, " ", 1);
		k++;
	}
	write(1, "(nil)", 5);
	k += 5;
	return (k);
}
