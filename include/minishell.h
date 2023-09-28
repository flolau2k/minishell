/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:04:39 by flauer            #+#    #+#             */
/*   Updated: 2023/09/28 09:33:21 by flauer           ###   ########.fr       */
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
# include "../libft/include/libft.h"
# include "structs.h"

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
# define A_CHAR "\'\"<>|"

extern int	g_sig;

// SRC
// CORE
// minishell.c
int		main(int argc, char **argv, char **env);
void	reset_shell(t_shell *sh);
void	main_loop(t_shell *sh);

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
void	do_execve(t_exec *exec);

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

// helper.c
bool	is_file(char *name);
void	do_builtin(t_fcn_p fcn, t_exec *exec);
void	exec_error(t_exec *exec, char *msg, char *error, int exitcode);

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
void	f_exit2(t_shell *sh, char *msg, int code);

// PARSE
// init.c
bool	init(t_shell *sh, int argc, char **argv, char **env);

// helpers.c
int		array_len(char **arr);
void	free_arr(char **arr);
void	wait_exit(void);
bool	is_valid_identfier(char *new);

// error.c
void	ft_error(char *msg, char *errmsg, int excode);
void	ft_error2(char *msg, char *errmsg);
void	ft_error3(char *msg, char *errmsg, int excode, void *tofree);

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

// lexer_utils.c
void	get_args(t_array *array, t_word *block, int *i, int count);
int		end_expression(char *instr, t_array *array);
void	join_array(char **array, char *file);
char	*ft_copystr(char *start, char *end);

// lexer_helper.c
int		redirect_type(t_token *token);
int		set_flag(char *c, int *i);
void	allocate_array(t_array *array, int count);
void	fill_array(t_array *array, t_word *word, int count, int flag);
bool	inside_quotes(char c);

// lexer.c
t_list	*do_lexing(char *arg);

// parser.c
bool	parser(t_list *token_str, t_cmd **root, t_shell *sh);
void	copy_expand(void *arg, t_shell *sh);
t_list	*unite_tokens(t_list *token_str);
bool	get_redirect(t_list **token_str, t_cmd **root, t_shell *sh);
bool	get_word(t_list **token_str, t_cmd **root, t_shell *sh);
bool	get_pipe(t_list **token_str, t_cmd **root);
bool	unite(t_list *tmp);
bool	is_redir(t_list *lst);

// token_utils.c
char	**array_addback(char **arr, char *new);
char	**make_array(t_list **elm);
t_list	*unite_tokens(t_list *token_str);
void	reset_flags(t_list *tmp);

// tree.c
void	arrange_pipe_tree(t_cmd **tree, t_pipe *node);
void	arrange_redir_tree(t_cmd **tree, t_redir *node);
void	arrange_command_tree(t_cmd **tree, t_exec *node);
void	print_tree(t_cmd **tree); // Test function

// tokenizer.c
bool	pipe_token(t_cmd **tree);
bool	redirect_token(t_list **elm, t_cmd **tree, t_shell *sh);
bool	command_token(char **argv, t_cmd **tree, t_shell *sh);

// expansion.c
char	*expand(char *arg, t_shell *sh);

// quote_check.c
bool	quote_check(char *arg);

// expand_utils.c
int		is_special_variable(t_shell *sh, char **new);
int		is_variable(t_shell *sh, char *arg, char **new);
int		not_variable(char *arg, char **new);
void	copy_expand(void *arg, t_shell *sh);
void	token_copy_expand(t_list *token_str, t_shell *sh);

// expand2_utils.c
int		get_special_var(t_shell *sh, char **ret);
int		get_variable(t_shell *sh, char *arg, char **ret);
int		get_non_variable(char *arg, char **ret);

// lexer_redirects.c
int		l_dless(t_list **ret, char *arg);
int		l_dgreater(t_list **ret, char *arg);
int		l_greater(t_list **ret, char *arg);
int		l_less(t_list **ret, char *arg);

// lexer_misc.c
int	l_word(t_list **ret, char *arg);
int	l_squote(t_list **ret, char *arg);
int	l_dquote(t_list **ret, char *arg);
int	l_pipe(t_list **ret, char *arg);
void	free_token(t_list *elm);

// basic_functions.c
size_t	ft_strlcat_s(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen_s(const char *s);
char	*ft_strjoin_s(char const *s1, char const *s2);

// list_utils.c
t_list	*delete_empty_nodes(t_list *root);
t_list	*delete_node(t_list **root, t_list *to_delete);
void	clear_redirects(t_list **token_str);
bool	unite(t_list *tmp);

// checkers.c
bool	is_redir(t_list *lst);
bool	is_pipe(t_list *lst);
bool	empty_node(t_list *node);
bool	flag_node(t_list *node);

#endif
