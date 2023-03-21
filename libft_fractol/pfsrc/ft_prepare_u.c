/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_u.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 10:28:45 by ggiannit          #+#    #+#             */
/*   Updated: 2022/10/27 12:35:54 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_fill_u_0(t_varpc *svar, char *utoa_var, char *u, ssize_t ua_len)
{
	while (svar->prec > ua_len++)
		*u++ = '0';
	u += ft_strlcpy_idu(svar, u, utoa_var, ua_len);
	if (*utoa_var == '0' && svar->prec == 0)
		ua_len--;
	while ((ssize_t) svar->length >= ua_len++)
		*u++ = ' ';
}

void	ft_fill_u_1(t_varpc *svar, char *utoa_var, char *u, ssize_t ua_len)
{
	ssize_t	k;

	k = svar->length;
	if (svar->prec == -1)
		svar->length -= ua_len;
	if ((svar->prec == 0 && *utoa_var == '0') || svar->prec > 0)
	{
		while ((ssize_t) svar->length-- > svar->prec)
			*u++ = ' ';
	}
	else if (svar->prec == 0)
	{
		while ((ssize_t) svar->length-- > ua_len)
			*u++ = ' ';
	}
	else
	{
		while ((ssize_t) svar->length-- > svar->prec + 1)
			*u++ = ' ';
	}
	while (svar->prec > ua_len++)
		*u++ = '0';
	svar->length = k;
	u += ft_strlcpy_idu(svar, u, utoa_var, ua_len);
}

int	ft_checkconflict_u(t_varpc *svar)
{
	if (svar->flag_32 || svar->flag_sharp || svar->flag_plus)
		return (0);
	if (svar->flag_zero)
	{
		if (svar->flag_dash || svar->prec != -1)
			svar->flag_zero = 0;
	}
	return (1);
}

void	ft_adjust_usize(t_varpc *svar, size_t *u_size)
{
	if (svar->length > *u_size || svar->prec > (ssize_t)(*u_size))
	{
		if ((ssize_t) svar->length > svar->prec)
		{
			if (svar->prec <= (ssize_t)(*u_size) && svar->prec != 0)
				svar->prec = -1;
			*u_size = svar->length;
		}
		else
			*u_size = (ssize_t) svar->prec;
	}
	else if (svar->prec <= (ssize_t)(*u_size) && svar->prec != 0)
		svar->prec = -1;
}

char	*ft_prepare_u(t_varpc *svar, unsigned int u_var)
{
	char	*u;
	char	*utoa_var;
	size_t	u_size;
	size_t	utoa_orig_size;

	if (!ft_checkconflict_u(svar))
		return (0);
	utoa_var = ft_lutoa((long unsigned int) u_var);
	utoa_orig_size = ft_strlen(utoa_var);
	u_size = utoa_orig_size;
	ft_adjust_usize(svar, &u_size);
	u = (char *) malloc((u_size + 1) * sizeof(char));
	if (!u)
		return (0);
	u[u_size] = '\0';
	if (svar->flag_dash)
		ft_fill_u_0(svar, utoa_var, u, (ssize_t) utoa_orig_size);
	else
		ft_fill_u_1(svar, utoa_var, u, (ssize_t) utoa_orig_size);
	u = ft_idu_handle_zero(svar, u, utoa_var[0]);
	free(utoa_var);
	return (u);
}
