/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:37:59 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/21 14:55:23 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av, char **envp)
{
	int i = 0;
	
	(void)ac;
	(void)av;
	while (envp[i])
		printf("%s\n", envp[i++]);
	printf("\n\n");
	char *name = getenv("USER");
	printf("name: %s\n", name);
}
