/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:04:39 by flauer            #+#    #+#             */
/*   Updated: 2023/08/28 10:18:11 by flauer           ###   ########.fr       */
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
int		execute(t_cmd *cmd);
int		do_exec(t_exec *exec);

// error.c
void	ft_error(char *msg, int excode);

// destructors.c
void	free_carr(char **arr);
void	free_exec(t_exec **arg);

// BUILTINS
// echo.c
int		f_echo(t_exec *cmd);

// cd.c
int		f_cd(t_exec *cmd);

// env.c
int		f_env(t_exec *cmd);

// exit.c
int		f_exit(t_exec *cmd);

// export.c
int		f_export(t_exec *cmd);

// pwd.c
int		f_pwd(t_exec *pwd);

// unset.c
int		f_unset(t_exec *cmd);

#endif