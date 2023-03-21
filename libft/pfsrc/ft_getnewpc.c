/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnewpc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:39:14 by ggiannit          #+#    #+#             */
/*   Updated: 2022/10/27 10:05:42 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_fill_id_1_32(t_varpc *svar, char *itoa_var, char *id, ssize_t ia_len)
{
	int	k;

	k = 0;
	if (svar->prec == 0 && *itoa_var == '0')
	{
		while ((ssize_t) svar->length-- > svar->prec)
			id[k++] = ' ';
	}
	else if (svar->prec == 0)
	{
		while ((ssize_t) svar->length-- > ia_len + 1)
			id[k++] = ' ';
	}
	else
	{
		while ((ssize_t)svar->length-- > svar->prec + 1)
			id[k++] = ' ';
	}
	return (k);
}

int	ft_strpclen(char *pc)
{
	int	k;

	k = 1;
	while (pc[k] == 32 || pc[k] == '+' || pc[k] == '-' || pc[k] == '.'
		|| pc[k] == '#' || ft_isdigit(pc[k]) || pc[k] == 'c'
		|| pc[k] == 's' || pc[k] == 'd' || pc[k] == 'i'
		|| pc[k] == 'u' || pc[k] == 'x' || pc[k] == 'x' || pc[k] == 'p')
	{
		if (pc[k] == 'c' || pc[k] == 's' || pc[k] == 'd' || pc[k] == 'i'
			|| pc[k] == 'u' || pc[k] == 'x' || pc[k] == 'x' || pc[k] == 'p')
			return (k);
		k++;
	}
	return (k);
}

int	ft_pcfinded(t_varpc **svar, char *pc)
{
	t_varpc	*newsvar;

	newsvar = ft_checkstrpc_endok(pc);
	if (newsvar)
	{
		if (!ft_checkstrpc_gook(pc, newsvar))
		{
			free(newsvar);
			return (0);
		}
		ft_svaradd_back(svar, newsvar);
	}
	else
		return (0);
	return (1);
}
