/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:04:39 by flauer            #+#    #+#             */
/*   Updated: 2023/08/21 15:18:36 by flauer           ###   ########.fr       */
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
bool	init(t_shell *shell, int argc, char **argv, char **env);

// environment.c
char	**get_env(char *env[], char *key);
char	*get_cmd(char *name, char *env[]);
char	*get_cmd_path(char *name, char *env[]);

// executor.c
void	execute(t_astnode *cmd);

// BUILTINS
// echo.c
void	echo(t_astnode *cmd);

// cd.c
void	cd(t_astnode *cmd);

// env.c
void	env(t_astnode *cmd);

// exit.c
void	exit(t_astnode *cmd);

// export.c
void	export(t_astnode *cmd);

// pwd.c
void	pwd(t_astnode *pwd);

// unset.c
void	unset(t_astnode *cmd);

#endif