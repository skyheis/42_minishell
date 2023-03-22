/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:55:13 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/22 15:30:51 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_linejoin(char *line, char *piece, int n)
{
	int		i;
	int		j;
	char	*newline;

	newline = ft_calloc(ft_strlen(line) + n + 1, sizeof(char));
	if (!newline)
		return (NULL);
	i = 0;
	j = 0;
	while (line && line[i])
	{
		newline[j] = line[i];
		i++;
		j++;
	}
	i = 0;
	while (piece && (piece[i] && i < n))
	{
		newline[j] = piece[i];
		i++;
		j++;
	}
	ft_free((void **) &line);
	return (newline);
}

char	*ft_parse_line(char *line)//, t_mish *meta)
{
	//itera, se trova '' fa cose, se trova "" fa cose, se trova $ fa cose
	int	i;
	int	n;
	char *newline;

	i = 0;
	newline = NULL;
	while (line[i])
	{
		n = 0;
		while (line[i + n] && line[i + n] != SQUT && line[i + n] != DQUT)
			n++;
		newline = ft_linejoin(newline, &line[i], n);
		if (!line[i + n])
			break ;
		i += n;
		n = 0;
		if (line[i] == SQUT)
		{
			i++;
			while (line[i + n] && line[i + n] != SQUT)
				n++;
			newline = ft_linejoin(newline, &line[i], n);
			i += n + 1;
		}
		else if (line[i] == DQUT)
		{
			i++;
			while (line[i + n] && line[i + n] != DQUT)
				n++;
			newline = ft_linejoin(newline, &line[i], n);
			i += n + 1;
		}
		else
			i++;
	}
	//ft_free((void **) &line);
	return (newline);
}

/*int main(int argc, char **argv)
{
	char *lol;

	while (1)
	{
		lol = readline("suca: ");
		add_history(lol);
		printf("%s\n", ft_parse_line(lol));
	}
	return 0;
}*/
