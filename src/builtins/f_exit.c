/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:10:39 by flauer            #+#    #+#             */
/*   Updated: 2023/10/12 10:47:04 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	num_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

bool	is_numeric(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] && (arg[i] == '+' || arg[i] == '-'))
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (false);
		i++;
	}
	if (i > 0)
		return (true);
	return (false);
}

static int	exit_error(t_exec *cmd, char *msg, char *errmsg, int code)
{
	free_exec(cmd);
	return (ft_error2(msg, errmsg, NULL, code));
}

int	f_exit(t_exec *cmd)
{
	int	code;

	code = 0;
	if (cmd->argv[1] && !is_numeric(cmd->argv[1]))
		exit(exit_error(cmd, "exit", "numeric argument required", 255));
	if (num_args(cmd->argv) > 2)
		return (exit_error(cmd, "exit", "too many arguments", GENERAL_ERROR));
	if (cmd->argv[1])
		code = ft_atoi(cmd->argv[1]);
	free_exec_shell(cmd);
	wait_exit();
	exit(code);
}

void	f_exit2(t_shell *sh, char *msg, int code)
{
	free_shell(sh);
	if (msg)
		ft_printf("%s\n", msg);
	exit(code);
}
