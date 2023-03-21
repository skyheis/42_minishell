# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/07 17:49:20 by ggiannit          #+#    #+#              #
#    Updated: 2023/01/20 12:28:46 by ggiannit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

####### NAME #########

PRNAME = libft

ARNAME = libft.a
ARDIR  = ../archive/

NAME = $(addprefix $(ARDIR),$(ARNAME))
INCLUDE = ../include

###### VARIABLE ######

CC = cc
AR = ar
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g

DIRSRCS = src/

FLSRCS = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
       ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_bzero.c \
       ft_atoi.c ft_calloc.c ft_tolower.c ft_toupper.c \
       ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
       ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
       ft_strmapi.c ft_striteri.c \
       ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
       ft_lstnew.c ft_lstadd_front.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
       ft_lstsize.c ft_lstlast.c ft_lstiter.c ft_lstmap.c \
	   ft_free_matrix.c ft_sleep_kinda.c ft_atoi_hex.c ft_ishex.c ft_count_in_str.c \
	   ft_iswhite.c

PF_DIRSRCS = pfsrc/

PF_FLSRCS = ft_printf.c ft_struct.c ft_checkstring.c ft_getnewpc.c \
	    ft_prepare_cs.c ft_prepare_id.c ft_prepare_p.c ft_prepare_u.c \
	    ft_prepare_x.c ft_handle_zeros.c ft_put.c ft_lutoa.c

GNL_DIRSRCS = gnlsrc/

GNL_FLSRCS = get_next_line.c get_next_line_utils.c

DIROBJS = obj/

FLOBJS = ${FLSRCS:.c=.o}
PF_FLOBJS = ${PF_FLSRCS:.c=.o}
GNL_FLOBJS = ${GNL_FLSRCS:.c=.o}

OBJS += $(addprefix $(DIROBJS),$(FLOBJS))
OBJS += $(addprefix $(DIROBJS),$(PF_FLOBJS))
OBJS += $(addprefix $(DIROBJS),$(GNL_FLOBJS))

#SRCS += $(addprefix $(DIRSRCS),$(FLSRCS))
#SRCS += $(addprefix $(PF_DIRSRCS),$(PF_FLSRCS))

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

$(DIROBJS)%.o: $(DIRSRCS)%.c
	@echo "$(GREEN)Compiling:$(BLUE) $< $(DEF_COLOR)"
	@${CC} ${CFLAGS} -I ${INCLUDE} -c $< -o $@

$(DIROBJS)%.o: $(PF_DIRSRCS)%.c
	@echo "$(GREEN)Compiling:$(BLUE) $< $(DEF_COLOR)"
	@${CC} ${CFLAGS} -I ${INCLUDE} -c $< -o $@

$(DIROBJS)%.o: $(GNL_DIRSRCS)%.c
	@echo "$(GREEN)Compiling:$(BLUE) $< $(DEF_COLOR)"
	@${CC} ${CFLAGS} -I ${INCLUDE} -c $< -o $@

####### RULES ########

all: ${NAME}

${NAME}: ${OBJS}
	@echo "$(YELLOW)- Archive Name: $(WHITE)${ARNAME}$(DEF_COLOR)"
	@echo "$(YELLOW)- Compiler: $(WHITE)${CC}$(DEF_COLOR)"
	@echo "$(YELLOW)- Flags: $(WHITE)${CFLAGS}$(DEF_COLOR)"
	@${AR} -rcs ${NAME} ${OBJS}

clean:
	@${RM} ${OBJS} 
	@echo "$(RED)All $(CYAN)$(PRNAME)$(RED)'s objects removed with $(WHITE)${RM}$(DEF_COLOR) 🧹" 

fclean: clean
	@${RM} ${NAME} 
	@echo "$(RED)..and $(CYAN)${ARNAME} $(RED)as been removed$(DEF_COLOR) 🚮"

re: fclean all

.PHONY: all clean fclean re starting .c.o
.SUFFIXES: .c .o 
