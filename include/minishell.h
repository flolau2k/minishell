/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:04:39 by flauer            #+#    #+#             */
/*   Updated: 2023/08/25 19:32:21 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "structs.h"
# include "../libft/include/libft.h"

// see https://tldp.org/LDP/abs/html/exitcodes.html
# define GENERAL_ERROR 1
# define BUILTIN_MISUSE 2
# define CMD_ERROR 126
# define CMD_NOT_FOUND 127
# define INVALID_ARG_EXIT 128
# define CTRL_C 130

# define R_CHAR "<>"
# define P_CHAR "|"
# define S_CHAR "<>|"

// minishell.c
int		main(int argc, char **argv, char **env);

// init.c
bool	init(t_shell *shell, int argc, char **argv, char **env);

// parser.c
void	*parser(char **str);

// environment.c
char	**get_env_s(char *env[], char *key);
char	*get_env(char *env[], char *key);
char	*get_cmd(char *name, char *env[]);
char	*get_cmd_path(char *name, char *env[]);

// lexer.c
t_cmd	*do_lexing(char *instr);

// lexer_utils.c
void		get_args(char ***start, char ***end, char *instr, char *instr_end);
int			redirect_type(char *instr);
char		*end_expression(char *instr);
void		arrange_tree(t_cmd **tree, void *node);
static bool	check_char(char c);
// void		split_args(char **start, char **end);

// tokenizer.c
int	pipe_token(char *instr, t_cmd *tree);
int	redirect_token(char *instr, t_cmd *tree);
int	command_token(char **start, char **end, t_cmd *tree);

// executor.c
void	f_execute(t_cmd *cmd);

// error.c
void	ft_error(char *msg, int excode);

// destructors.c
void	free_carr(char **arr);
void	free_exec(t_exec **arg);

// BUILTINS
// echo.c
void	f_echo(t_exec *cmd);

// cd.c
void	f_cd(t_exec *cmd);

// env.c
void	f_env(t_exec *cmd);

// exit.c
void	f_exit(t_exec *cmd);

// export.c
void	f_export(t_exec *cmd);

// pwd.c
void	f_pwd(t_exec *pwd);

// unset.c
void	f_unset(t_exec *cmd);

#endif