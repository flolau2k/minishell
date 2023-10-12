# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/08 12:51:09 by flauer            #+#    #+#              #
#    Updated: 2023/10/12 17:19:30 by flauer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		minishell

CC =		cc
CFLAGS =	-Wall -Wextra -Werror -g

LIBFTDIR =	libft
LIBFT =		$(LIBFTDIR)/libft.a
LIBS =		$(LIBFT) -lreadline

OBJDIR =	obj
SRCDIR =	src
INCDIR =	include
VPATH = 	$(SRCDIR)/core $(SRCDIR)/builtins $(SRCDIR)/parse $(SRCDIR)/test \
			$(SRCDIR)/utils $(SRCDIR)/error
INCLUDES =	-I$(INCDIR) -I$(LIBFTDIR)/include
HEADERS =	include/minishell.h

#src/parse
FILES =		lexer.c init.c tree.c tokenizer.c expansion.c quote_check.c parser.c
#src/core
FILES +=	executor.c minishell.c environment.c here_doc.c pipe.c \
			environment_helper.c signals.c helper.c
#src/builtins
FILES +=	f_cd.c f_echo.c f_env.c f_exit.c f_export.c f_pwd.c f_unset.c \
			builtins.c
#src/utils
FILES +=	destructors.c helpers.c token_utils.c expand_utils.c \
			expand2_utils.c non_alloc_destructors.c destructors_single.c \
			destructors_shell.c lexer_helper.c lexer_redirects.c lexer_misc.c \
			basic_functions.c list_utils.c checkers.c
#src/error
FILES +=	error.c

OBJ = 		$(addprefix $(OBJDIR)/, $(FILES:%.c=%.o))

multi:
	$(MAKE) -j12 all

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@echo "built $(NAME)"

$(OBJDIR)/%.o: %.c $(HEADERS) $(LIBFT) | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	make -C libft clean
	/bin/rm -rf $(OBJDIR)

fclean: clean
	make -C libft fclean
	/bin/rm -rf $(NAME)

re:	fclean multi

$(LIBFT):
	@git submodule update --init --recursive
	@$(MAKE) -C $(@D)

.PHONY =	all clean fclean re bonus
