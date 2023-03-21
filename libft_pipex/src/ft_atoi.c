/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:57:11 by ggiannit          #+#    #+#             */
/*   Updated: 2022/10/08 11:48:05 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int	k;
	int	sgn;
	int	toi;

	k = 0;
	toi = 0;
	sgn = 1;
	while (nptr[k] == 32 || (nptr[k] >= 9 && nptr[k] <= 13))
		k++;
	if (nptr[k] == '-' || nptr[k] == '+')
	{
		if (nptr[k] == '-')
			sgn = -1;
		k++;
	}
	while (nptr[k] >= '0' && nptr[k] <= '9')
	{
		toi *= 10;
		toi += nptr[k] - 48;
		k++;
	}
	return (toi * sgn);
}

/*int	main(int ac, char **av)
{
	if (ac != 2)
		return 1;
	printf("%i\n", ft_atoi(av[1]));
	return 0;
}*/
