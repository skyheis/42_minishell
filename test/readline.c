/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:52:35 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/21 10:30:21 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
	char *line;
	int i = 0;
	
	while (0)
	{
		line = readline("culo: ");
		printf("tette is: %s\n", line);
		add_history(line);
		if (i == 5)
			rl_clear_history();
		free(line);
		i++;
	} 
	unlink("me");
	//line = getcwd();
	//printf("pwd is: %s\n", line);
}
