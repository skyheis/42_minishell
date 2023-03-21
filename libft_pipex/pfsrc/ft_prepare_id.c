/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_id.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:14:45 by ggiannit          #+#    #+#             */
/*   Updated: 2022/10/27 12:34:17 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_fill_id_1(t_varpc *svar, char *itoa_var, char *id, ssize_t ia_len)
{
	if ((svar->flag_plus || svar->flag_32)
		&& svar->prec == -1 && itoa_var[0] != '-')
		svar->length--;
	if (itoa_var[0] != '-' && !svar->flag_plus && !svar->flag_32
		&& svar->prec != -1)
		svar->length++;
	if (svar->prec == -1)
		svar->length -= ia_len;
	id += ft_fill_id_1_32(svar, itoa_var, id, ia_len);
	if (itoa_var[0] != '-' && svar->flag_plus)
		*id++ = '+';
	else if (itoa_var[0] != '-' && svar->flag_32)
		*id++ = ' ';
	else if (itoa_var[0] == '-')
		*id++ = '-';
	if (itoa_var[0] == '-')
		ia_len--;
	while (svar->prec > ia_len++)
		*id++ = '0';
	if (itoa_var[0] == '-')
		id += ft_strlcpy_idu(svar, id, &itoa_var[1], ia_len);
	else
		id += ft_strlcpy_idu(svar, id, itoa_var, ia_len);
}

void	ft_fill_id_0(t_varpc *svar, char *itoa_var, char *id, ssize_t ia_len)
{
	if (itoa_var[0] != '-' && svar->flag_plus)
		*id++ = '+';
	else if (itoa_var[0] != '-' && svar->flag_32)
		*id++ = ' ';
	else if (itoa_var[0] == '-')
		*id++ = '-';
	if (itoa_var[0] == '-')
		ia_len--;
	while (svar->prec > ia_len++)
		*id++ = '0';
	if (itoa_var[0] == '-')
		id += ft_strlcpy_idu(svar, id, &itoa_var[1], ia_len);
	else
		id += ft_strlcpy_idu(svar, id, itoa_var, ia_len);
	if (itoa_var[0] != '-' && !svar->flag_plus && !svar->flag_32)
		ia_len--;
	if (*itoa_var == '0' && svar->prec == 0)
		ia_len--;
	while ((ssize_t) svar->length > ia_len++)
		*id++ = ' ';
}

int	ft_checkconflict_id(t_varpc *svar)
{
	if (svar->flag_32)
	{
		if (svar->flag_plus)
			svar->flag_32 = 0;
	}
	if (svar->flag_zero)
	{
		if (svar->flag_dash || svar->prec != -1)
			svar->flag_zero = 0;
	}
	if (svar->flag_sharp
		&& (svar->ascii == 'd' || svar->ascii == 'i'))
		return (0);
	return (1);
}

void	ft_adjust_idsize(t_varpc *svar, size_t *id_size,
		size_t itoa_orig_size, char itoa_0)
{
	if (svar->length > *id_size || svar->prec > (ssize_t)(*id_size))
	{
		if ((ssize_t) svar->length > svar->prec)
		{
			if (svar->prec <= (ssize_t)(*id_size)
				&& svar->prec != 0 && !svar->flag_dash)
				svar->prec = -1;
			*id_size = svar->length;
		}
		else
			*id_size = (ssize_t) svar->prec;
	}
	if (svar->flag_32 || svar->flag_plus)
	{
		if ((ssize_t)(*id_size) == svar->prec && itoa_orig_size < *id_size)
			*id_size = *id_size + 1;
		if (*id_size == itoa_orig_size && itoa_0 != '-')
			*id_size = *id_size + 1;
	}
}

char	*ft_prepare_id(t_varpc *svar, int id_var)
{
	char	*id;
	char	*itoa_var;
	size_t	id_size;
	size_t	itoa_orig_size;

	if (!ft_checkconflict_id(svar))
		return (0);
	itoa_var = ft_itoa(id_var);
	itoa_orig_size = ft_strlen(itoa_var);
	id_size = itoa_orig_size;
	ft_adjust_idsize(svar, &id_size, itoa_orig_size, itoa_var[0]);
	if (itoa_var[0] == '-' && (ssize_t) id_size == svar->prec)
		id_size++;
	id = (char *) malloc((id_size + 1) * sizeof(char));
	if (!id)
		return (0);
	id[id_size] = '\0';
	if (svar->flag_dash)
		ft_fill_id_0(svar, itoa_var, id, (ssize_t) itoa_orig_size);
	else
		ft_fill_id_1(svar, itoa_var, id, (ssize_t) itoa_orig_size);
	id = ft_idu_handle_zero(svar, id, itoa_var[0]);
	free(itoa_var);
	return (id);
}
