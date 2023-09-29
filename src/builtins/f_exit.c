/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:10:39 by flauer            #+#    #+#             */
/*   Updated: 2023/09/29 14:24:15 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		num_args(char **argv)
{
	int	i;

	i = 0;
	while(argv[i])
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

int	f_exit(t_exec *cmd)
{
	int	code;

	code = 0;
	if (cmd->argv[1] && !is_numeric(cmd->argv[1]))
		ft_error("exit", "numeric argument required", 255);
	if (num_args(cmd->argv) > 2)
		return (ft_error2("exit", "too many arguments", NULL, GENERAL_ERROR));
	if (cmd->argv[1])
		code = ft_atoi(cmd->argv[1]);
	free_shell(cmd->sh);
	free_exec(cmd);
	wait_exit();
	exit(code);
}

void	f_exit2(t_shell *sh, char *msg, int code)
{
	free_shell(sh);
	if (msg)
		printf("%s\n", msg);
	exit(code);
}
