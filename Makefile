# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/07 17:49:20 by ggiannit          #+#    #+#              #
#    Updated: 2023/04/13 11:10:59 by ggiannit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

####### NAME #########

NAME = minishell
BNUS = bonus

###### VARIABLE ######

INCLUDE = include

DIRSRCS =
DIROBJS = obj/

FLSRCS = main.c cmd_list.c custom_env.c parse_line.c handle_readline.c \
		 splitered.c splitermux.c parse_red.c\
		 env_list.c find_binary.c buildin.c buildin_export.c \
		 handle_commands.c buildin_cd_utils.c \
		 buildin_cd.c buildin_cd2.c handle_setenv.c \
		 mini_pipe.c sign_handler.c redirect.c duck.c

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

cool:
# coool Script #
	clear
	for i in 1 2 3 ; do \
	echo "$(YELLOW)音Welcome to Minishell音$(DEF_COLOR)" \
	&& sleep 0.4 \
	&& clear \
	&& echo "$(GREEN)音Welcome to Minishell音$(DEF_COLOR)" \
	&& sleep 0.4 \
	&& clear ; done
	echo "READY"
	sleep 0.3
	echo "-"
	sleep 0.2
	echo "--"
	sleep 0.2
	echo "---"
	sleep 0.5
	clear
	echo "ᕙ( ︡’︡ 益 ’︠)ง▬▬█"
	sleep 2.05
	clear


.PHONY: all clean fclean re starting .c.o cool libft libftclean libftfclean valgrind
.SUFFIXES: .c .o
.SILENT:
