# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/07 17:49:20 by ggiannit          #+#    #+#              #
#    Updated: 2023/04/15 18:31:37 by ggiannit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

####### NAME #########

NAME = minishell
BNUS = bonus

###### VARIABLE ######

INCLUDE = include

DIRSRCS =
DIROBJS = obj/

FLSRCS = main.c handle_readline.c free_n_history.c print_file.c \
		 parse_line.c parse_red.c find_binary.c \
		 buildin.c buildin_unset.c buildin_export.c \
		 buildin_cd.c buildin_cd2.c buildin_cd_utils.c \
		 env_list.c custom_env.c env_utils.c \
		 handle_commands.c handle_setenv.c cmd_list.c \
		 buildin_cd2_utils.c parse_red_utils.c\
		 mini_pipe.c mini_pipe_utils.c parse_line_utils.c\
		 splitered.c splitered_utils.c \
		 splitermux.c splitermux_utils_0.c splitermux_utils_1.c \
		 sign_handler.c redirect.c redirect_utils.c duck.c

FLOBJS = ${FLSRCS:.c=.o}

OBJS = $(addprefix $(DIROBJS),$(FLOBJS))

ARUSD = libft.a
ARUSDDIR = archive/

ARINC = $(addprefix $(ARUSDDIR),$(ARUSD))

CC = cc
AR = ar
RM = rm -f
CFLAGS = -g -Wall -Wextra -Werror
MINIFLAGS = -lreadline

###### COLORS ########

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

######## EXT #########

# make a .o file using a .c file
# $< for the .c file
# $@ for the .o file

# .inextention.outextention:

#.c.o:
$(DIROBJS)%.o: $(DIRSRCS)%.c
	@echo "$(GREEN)Compiling:$(BLUE) $< $(DEF_COLOR)"
	@${CC} ${CFLAGS} -I ${INCLUDE} -c $< -o $@

####### RULES ########

all: libft ${NAME} #cool

${NAME}: ${OBJS}
	@echo "$(YELLOW)- Program Name: $(WHITE)${NAME}$(DEF_COLOR)"
	@echo "$(YELLOW)- Compiler: $(WHITE)${CC}$(DEF_COLOR)"
	@echo "$(YELLOW)- Flags: $(WHITE)${CFLAGS} ${MINIFLAGS}$(DEF_COLOR)"
	@${CC} ${CFLAGS} -L $(ARUSDDIR) -I $(INCLUDE) -o $(NAME) $(OBJS) $(ARINC) $(MINIFLAGS)

clean:
	@make -sC libft clean
	@${RM} ${OBJS} 
	@echo "$(RED)All $(CYAN)$(NAME)$(RED)'s objects removed with $(WHITE)${RM} $(YELLOW)*QUACK*$(DEF_COLOR)"

fclean: clean
	@make -sC libft fclean
	@${RM} ${NAME} 
	@echo "$(RED)..and $(CYAN)${NAME} $(RED)as been removed$(DEF_COLOR) 🦆🦆"

libft:
	@make -sC libft

libftclean:
	@make -sC libft clean

libftfclean:
	@make -sC libft fclean

re: fclean all

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=./readline.supp ./minishell

.PHONY: all clean fclean re starting .c.o cool libft libftclean libftfclean valgrind
.SUFFIXES: .c .o
.SILENT:
