/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:21:50 by ggiannit          #+#    #+#             */
/*   Updated: 2022/10/08 10:50:18 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
	{
		return (c - 32);
	}
	return (c);
}

/*#include <stdio.h>

int	main(void)
{
	printf("%i ", ft_toupper('a'));
	printf("%i ", ft_toupper('A'));
	printf("%i ", ft_toupper('.'));
	printf("%i ", ft_toupper('z'));
}*/
