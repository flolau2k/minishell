# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/08 12:51:09 by flauer            #+#    #+#              #
#    Updated: 2023/09/13 16:41:28 by flauer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		minishell
T_NAME =	tests
TEST =		test_minishell

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
FILES =		lexer.c parser.c init.c tree.c tokenizer.c expansion.c quote_check.c
#src/core
FILES +=	executor.c minishell.c environment.c here_doc.c pipe.c \
			environment_helper.c signals.c
#src/builtins
FILES +=	f_cd.c f_echo.c f_env.c f_exit.c f_export.c f_pwd.c f_unset.c \
			builtins.c
#src/utils
FILES +=	destructors.c helpers.c lexer_utils.c token_utils.c expand_utils.c \
			expand2_utils.c non_alloc_destructors.c destructors_single.c
#src/error
FILES +=	error.c
#src/test
T_FILES =	test.c

OBJ = 		$(addprefix $(OBJDIR)/, $(FILES:%.c=%.o))
T_OBJ =		$(addprefix $(OBJDIR)/, $(T_FILES:%.c=%.o))

all: $(NAME)

debug: CFLAGS += -g 
debug: clean all

tests: CFLAGS += -g
tests: $(TEST)

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

fclean: clean
	make -C libft fclean
	/bin/rm -rf $(NAME)
	/bin/rm -rf $(T_NAME)
	/bin/rm -rf $(TEST)

re:	fclean all

$(LIBFT):
	@git submodule update --init --recursive
	@$(MAKE) -C $(@D)

$(TEST): $(LIBFT) $(T_OBJ) $(OBJ)
	$(CC) $(OBJ) $(T_OBJ) $(LIBS) -o $(TEST)

.PHONY =	all clean fclean re bonus

$(T_NAME): CFLAGS += -g
$(T_NAME): $(LIBFT) $(T_OBJ) $(OBJ)
	$(CC) $(CFLAGS) $(T_OBJ) $(OBJ) $(LIBS) -o $(T_NAME)
