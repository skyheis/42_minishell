/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_reline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:06:18 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/21 10:09:00 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char* line = readline("Enter a command: ");
    if (line) {
        // Print the original input
        printf("Original input: %s\n", line);

        // Replace the input with a new string
        rl_replace_line("new command", 0);

        // Redisplay the modified input
        rl_redisplay();

        printf("Original input: %s\n", line);
        // Read the modified input
        char* new_line = readline(NULL);
        if (new_line) {
            printf("Modified input: %s\n", new_line);
            free(new_line);
        }
        free(line);
    }
}
