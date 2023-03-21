/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strerror.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:44:34 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/21 10:50:47 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main () {
   int fd;

   fd = open("file.txt", O_RDONLY);
   if( fd == -1 ) {
      printf("Error: %s\n", strerror(EACCES));
   }
   
   return(0);
}
