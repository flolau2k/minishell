/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:04:39 by flauer            #+#    #+#             */
/*   Updated: 2023/08/31 15:32:34 by pcazac           ###   ########.fr       */
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

# define HERE_DOC_PROMPT "(heredoc)> "
# define MINISHELL_PROMPT "> "

// see https://tldp.org/LDP/abs/html/exitcodes.html
# define GENERAL_ERROR 1
# define BUILTIN_MISUSE 2
# define CMD_ERROR 126
# define CMD_NOT_FOUND 127
# define INVALID_ARG_EXIT 128
# define CTRL_C 130

# define O_HEREDOC 0x0010

# define R_CHAR "<>"
# define P_CHAR "|"
# define S_CHAR "<>|"

// minishell.c
int		main(int argc, char **argv, char **env);

// init.c
bool	init(t_shell *sh, int argc, char **argv, char **env);

// environment.c
char	**set_env(char **env, char *newval);
char	**get_env_arr(char *env[], char *key);
char	*get_env(char *env[], char *key);
char	*get_cmd(char *name, char *env[]);
char	*get_cmd_path(char *name, char *env[]);

// helpers.c
int		array_len(char **arr);
void	free_arr(char ***arr);
char	**get_env_arr(char *env[], char *key);

// executor.c
void	execute(t_cmd *cmd);
void	do_exec(t_exec *exec);
void	do_pipe(t_pipe *cmd);
void	do_redir(t_redir *redir);
void	do_execve(t_exec *exec);

// error.c
void	ft_error(char *msg, int excode);

// destructors.c
void	free_carr(char **arr);
void	free_exec(t_exec **arg);

// core/pipe.c
pid_t	create_pipe(void (f1)(t_cmd *), t_cmd *a1);
pid_t	create_pipe_c(void (f1)(char *), char *a1);

// core/here_doc.c
void	here_doc(char *lim);
void	hd_child(char *lim);

// parser.c
void	do_parsing(t_cmd *str);

// lexer_utils.c
void	get_args(t_array *array, t_word block, int i, int count);
int		redirect_type(char *instr);
int		end_expression(char *instr, t_word *word);
bool	check_char(char c);

// lexer.c
t_cmd	*do_lexing(t_shell *sh);

// token_utils.c
int	new_arr(t_array *array, int count);

// tree.c
void	arrange_pipe_tree(t_cmd **tree, t_pipe *node);
void	arrange_redir_tree(t_cmd **tree, t_redir *node);
void	arrange_command_tree(t_cmd **tree, t_exec *node);
void	print_tree(t_cmd **tree); // Test function

// environment.c
char	**get_env_s(char *env[], char *key);
char	*get_env(char *env[], char *key);
char	*get_cmd(char *name, char *env[]);
char	*get_cmd_path(char *name, char *env[]);

// tokenizer.c
t_cmd	*pipe_token(t_cmd **tree);
int		redirect_token(char *instr, t_cmd **tree);
int		command_token(t_shell *sh, t_array *array, t_cmd **tree);

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