/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:24:21 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/14 09:41:53 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clean_for_file(char **env)
{
	char	*clean_path[2];

	clean_path[0] = ft_strjoin(NULL, "/usr/bin/clear");
	clean_path[1] = NULL;
	if (!clean_path[0])
		return ;
	if (!fork())
	{
		execve("/usr/bin/clear", clean_path, env);
		exit(1);
	}
	wait(NULL);
	ft_free_null(clean_path);
}

void	ft_print_file(t_mish *meta, char *filename)
{
	int		fd;
	int		b_readed;
	char	*file_memory;
	char	*full_badge;

	ft_clean_for_file(meta->env);
	fd = open(filename, O_RDONLY);
	b_readed = READ_SIZE;
	full_badge = NULL;
	if (fd == -1)
		return ;
	while (b_readed == READ_SIZE)
	{
		file_memory = (char *) ft_calloc(READ_SIZE + 1, sizeof(char));
		b_readed = read(fd, file_memory, READ_SIZE);
		if (b_readed == -1)
		{
			ft_free((void **) &(file_memory));
			return ;
		}
		full_badge = ft_strjoin_free(full_badge, file_memory);
	}
	close(fd);
	printf("%s", full_badge);
	ft_free((void **) &(full_badge));
}
