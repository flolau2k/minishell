/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:04:39 by flauer            #+#    #+#             */
/*   Updated: 2023/09/15 10:35:02 by flauer           ###   ########.fr       */
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
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "structs.h"
# include "../libft/include/libft.h"

# define NO_COLOR "\033[0m"

# define HERE_DOC_PROMPT "(heredoc)> "
# define MINISHELL_PROMPT "minishell> "

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

extern int	g_sig;

// SRC
// CORE
// minishell.c
int		main(int argc, char **argv, char **env);

// pipe.c
pid_t	create_pipe(void (f1)(t_cmd *), t_cmd *a1, t_cmd *tofree);
pid_t	execute_command_pipe(char *cmd, char **argv);
char	*execute_command(char *cmd, char **argv);
void	close_pipe(int *pipe_fd);

// here_doc.c
void	here_doc(t_redir *redir);
void	hd_child(t_cmd *red);

// executor.c
void	rec_execute(t_cmd *cmd);
void	do_exec(t_exec *exec);
void	do_pipe(t_pipe *cmd);
void	do_redir(t_redir *redir);
void	do_builtin(t_fcn_p fcn, t_exec *exec);
void	exec_error(t_exec *exec, char *msg, char *error);
void	do_execve(t_exec *exec);

// signals.c
void	signal_handler(int signo);

// BUILTINS
t_fcn_p	get_builtin(t_exec *exec);
int		f_echo(t_exec *cmd);
int		f_cd(t_exec *cmd);
int		f_env(t_exec *cmd);
int		f_exit(t_exec *cmd);
int		f_export(t_exec *cmd);
int		f_pwd(t_exec *pwd);
int		f_unset(t_exec *cmd);
void	f_exit2(char *msg, int code);

// PARSE
// init.c
bool	init(t_shell *sh, int argc, char **argv, char **env);

// environment.c
char	**set_env(char **env, char *newval);
char	*get_env(char **env, char *key);
char	**unset_env(char **env, char *val);
bool	replace_in_env(char **env, char *new);
char	**copy_env(char **env);

// environment_helper.c
char	*get_cmd_path(char *name, char **env);
char	**get_env_s(char **env, char *key);
char	*get_cmd(char *name, char **env);
char	**set_default_env(char **env);

// helpers.c
int		array_len(char **arr);
void	free_arr(char **arr);
void	wait_exit(void);

// error.c
void	ft_error(char *msg, char *errmsg, int excode);
void	ft_error2(char *msg, int excode);

// destructors.c
void	free_tree(t_cmd *cmd);
void	free_exec(t_exec *arg);
void	free_pipe(t_pipe *arg);
void	free_redir(t_redir *arg);

// non_alloc_destructors.c
void	free_init_tree(t_cmd *cmd);

// destructors_single.c
void	free_shell(t_shell *sh);
void	free_pipe_single(t_pipe *arg);
void	free_redir_single(t_redir *arg);

// destructors_shell.c
void	free_tree_shell(t_cmd *cmd);
void	free_exec_shell(t_exec *arg);
void	free_pipe_shell(t_pipe *arg);
void	free_redir_shell(t_redir *arg);

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
int		new_arr(t_array *array, int count);

// tree.c
void	arrange_pipe_tree(t_cmd **tree, t_pipe *node);
void	arrange_redir_tree(t_cmd **tree, t_redir *node);
void	arrange_command_tree(t_cmd **tree, t_exec *node);
void	print_tree(t_cmd **tree); // Test function

// tokenizer.c
t_cmd	*pipe_token(t_cmd **tree);
int		redirect_token(char *instr, t_cmd **tree, t_shell *sh);
int		command_token(t_shell *sh, t_array *array, t_cmd **tree);

// expansion.c
void	expander(t_shell *sh, t_cmd *cmd);

// quote_check.c
bool	quote_check(t_cmd *cmd);

// expand_utils.c
char	*ft_realloc(char *ret, char *s, int count);
int		is_special_variable(t_shell *sh, char **new);
int		is_variable(t_shell *sh, char *arg, char **new);
int		not_variable(char *arg, char **new);

// expand2_utils.c
int	get_special_var(t_shell *sh, char **ret);
int	get_variable(t_shell *sh, char *arg, char **ret);
int	get_non_variable(char *arg, char **ret);

// BUILTINS

#endif

