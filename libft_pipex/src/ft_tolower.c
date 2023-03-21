/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:21:50 by ggiannit          #+#    #+#             */
/*   Updated: 2022/10/06 16:25:52 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
	{
		return (c + 32);
	}
	return (c);
}

/*int	main(void)
{
	printf("%c ", ft_tolower('a'));
	printf("%c ", ft_tolower('A'));
	printf("%c ", ft_tolower('.'));
	printf("%c ", ft_tolower('Z'));
}*/
