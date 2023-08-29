/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:04:39 by flauer            #+#    #+#             */
/*   Updated: 2023/08/29 11:26:44 by flauer           ###   ########.fr       */
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
# include "libft.h"

# define HERE_DOC_PROMPT "> "

// see https://tldp.org/LDP/abs/html/exitcodes.html
# define GENERAL_ERROR 1
# define BUILTIN_MISUSE 2
# define CMD_ERROR 126
# define CMD_NOT_FOUND 127
# define INVALID_ARG_EXIT 128
# define CTRL_C 130

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

// lexer.c
t_cmd	*do_lexing(char *instr, t_cmd *root);
// helpers.c
int		array_len(char **arr);

// executor.c
void	execute(t_cmd *cmd);
void	do_exec(t_exec *exec);

// error.c
void	ft_error(char *msg, int excode);

// destructors.c
void	free_carr(char **arr);
void	free_exec(t_exec **arg);

// core/pipe.c
pid_t	create_pipe(void (f1)(void *), void *a1);
void	hd_child(void *arg);

// core/here_doc.c
void	here_doc(t_args *args);
void	hd_child(void *arg);

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