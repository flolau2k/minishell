/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:04:39 by flauer            #+#    #+#             */
/*   Updated: 2023/08/22 13:52:43 by flauer           ###   ########.fr       */
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
int	main(int argc, char **argv, char **env);

// init.c
bool	init(int argc, char **argv, char **env);

// environment.c
char	**get_env(char *env[], char *key);
char	*get_cmd(char *name, char *env[]);
char	*get_cmd_path(char *name, char *env[]);

// executor.c
void	f_execute(t_cmd *cmd);

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