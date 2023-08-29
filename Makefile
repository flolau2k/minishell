# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/08 12:51:09 by flauer            #+#    #+#              #
#    Updated: 2023/08/29 13:53:20 by pcazac           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		minishell
T_NAME =	tests

CC =		cc
CFLAGS =	-Wall -Wextra -Werror

LIBFTDIR =	libft
LIBFT =		$(LIBFTDIR)/libft.a
LIBS =		$(LIBFT)

OBJDIR =	obj
SRCDIR =	src
INCDIR =	include
VPATH = 	$(SRCDIR)/core $(SRCDIR)/builtins $(SRCDIR)/parse $(SRCDIR)/test \
			$(SRCDIR)/utils $(SRCDIR)/error
INCLUDES =	-I$(INCDIR) -I$(LIBFTDIR)/include

HEADERS =	include/minishell.h

#src/parse
FILES =		lexer.c parser.c init.c  tokenizer.c tree.c

#src/core
# FILES +=	minishell.c environment.c executor.c

#src/builtins
# FILES +=	f_cd.c f_echo.c f_env.c f_exit.c f_export.c f_pwd.c f_unset.c

#src/utils
FILES +=	lexer_utils.c
# destructors.c helpers.c 
#src/error
FILES +=	error.c

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
	/bin/rm -rf $(T_NAME)

re:	fclean all

$(LIBFT):
	@git submodule update --init --recursive
	@make -C $(@D)

.PHONY =	all clean fclean re bonus

$(T_NAME): CFLAGS += -g
$(T_NAME): $(T_OBJ) $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(T_OBJ) $(OBJ) $(LIBS) -o $(T_NAME)
