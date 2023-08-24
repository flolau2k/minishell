# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/08 12:51:09 by flauer            #+#    #+#              #
#    Updated: 2023/08/24 13:54:47 by flauer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		minishell

CC =		cc
CFLAGS =	-Wall -Wextra -Werror

LIBFTDIR =	libft
LIBFT =		$(LIBFTDIR)/libft.a
LIBS =		$(LIBFT)

OBJDIR =	obj
SRCDIR =	src
INCDIR =	include
VPATH = 	$(SRCDIR)/core $(SRCDIR)/init $(SRCDIR)/builtins $(SRCDIR)/parse $(SRCDIR)/test
INCLUDES =	-I$(INCDIR) -I$(LIBFTDIR)/include

HEADERS =	include/minishell.h

#src/init
FILES =		lexer.c parser.c minishell.c

#src/core
FILES +=	minishell.c

#src/test
T_FILES =	test.c

OBJ = 		$(addprefix $(OBJDIR)/, $(FILES:%.c=%.o))
T_OBJ =		$(addprefix $(OBJDIR)/, $(T_FILES:%.c=%.o))


all: $(NAME)

debug: CFLAGS += -g
debug: clean all

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@echo "built $(NAME)"

$(OBJDIR)/%.o: %.c $(HEADERS) | $(OBJDIR)
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

re:	fclean all

$(LIBFT):
	@git submodule update --init --recursive
	@make -C $(@D)

.PHONY =	all clean fclean re bonus
