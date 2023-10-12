/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:10:26 by flauer            #+#    #+#             */
/*   Updated: 2023/10/12 15:49:39 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	check_nflag(char *arg)
{
	int	i;

	i = 1;
	if (!arg || arg[0] != '-')
		return (false);
	while (arg[i] == 'n')
		i++;
	if (arg[i])
		return (false);
	return (true);
}

int	f_echo(t_exec *cmd)
{
	int		i;
	bool	nl;

	nl = true;
	i = 1;
	while (check_nflag(cmd->argv[i]))
	{
		nl = false;
		i++;
	}
	while (cmd->argv[i] && cmd->argv[i + 1])
	{
		ft_printf("%s ", cmd->argv[i]);
		i++;
	}
	if (cmd->argv[i])
		ft_printf("%s", cmd->argv[i]);
	if (nl)
		ft_printf("\n");
	if (cmd->pid == -1)
		free_exec(cmd);
	return (EXIT_SUCCESS);
}
