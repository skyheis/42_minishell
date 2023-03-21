/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:51:14 by ggiannit          #+#    #+#             */
/*   Updated: 2022/10/27 12:41:35 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_svaradd_back(t_varpc **svar, t_varpc *new)
{
	t_varpc	*tmp;

	if (*svar == NULL)
		*svar = new;
	else
	{
		tmp = (*svar);
		while ((*svar)->next != NULL)
			(*svar) = (*svar)->next;
		(*svar)->next = new;
		*svar = tmp;
	}
}

void	ft_svarclear(t_varpc **svar)
{
	t_varpc	*tmp;

	tmp = NULL;
	while (*svar)
	{
		tmp = (*svar)->next;
		free(*svar);
		(*svar) = tmp;
	}
}

t_varpc	*ft_svarnew(char ascii)
{
	t_varpc	*new;

	new = malloc(sizeof(t_varpc));
	if (!new)
		return (NULL);
	new->ascii = ascii;
	new->length = 0;
	new->prec = -1;
	new->flag_32 = 0;
	new->flag_plus = 0;
	new->flag_sharp = 0;
	new->flag_dash = 0;
	new->flag_zero = 0;
	new->next = NULL;
	return (new);
}
