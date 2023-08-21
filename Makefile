# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/08 12:51:09 by flauer            #+#    #+#              #
#    Updated: 2023/08/21 13:43:25 by flauer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		minishell
T_NAME =	tests

CC =		cc
CFLAGS =	-Wall -Wextra -Werror

LIBFTDIR =	libft
LIBFT =		$(LIBFTDIR)/libft.a
LIBS =		$(LIBFT)

INCLUDES =	-Iinclude -I$(LIBFTDIR)/include

OBJDIR =	obj
SRCDIR =	src
INCDIR =	include

FILES =		lexer.c
T_FILES =	test.c
HEADER_F =	minishell.h

SRC =		$(addprefix $(SRCDIR)/, $(FILES))
SRC_T =		$(addprefix $(SRCDIR)/, $(T_FILES))
OBJ =		$(addprefix $(OBJDIR)/, $(FILES:%.c=%.o))
T_OBJ =		$(addprefix $(OBJDIR)/, $(T_FILES:%.c=%.o))
HEADERS =	$(addprefix $(INCDIR)/, $(HEADER_F))

all: $(NAME)

debug: CFLAGS += -g
debug: clean all

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@echo "built $(NAME)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS) | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	make -C libft clean
	/bin/rm -rf $(OBJDIR)
	/bin/rm -rf $(OBJDIR_B)

fclean: clean
	make -C libft fclean
	/bin/rm -rf $(NAME)
	/bin/rm -rf $(T_NAME)

re:	fclean all

$(LIBFT):
	@git submodule update --init --recursive
	@make -C $(@D)

.PHONY =	all clean fclean re bonus

$(T_NAME): CFLAGS += -g
$(T_NAME): $(T_OBJ) $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(T_OBJ) $(OBJ) $(LIBS) -o $(T_NAME)
