/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:10:31 by flauer            #+#    #+#             */
/*   Updated: 2023/09/28 16:52:10 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	f_cd(t_exec *cmd)
{
	char	*dir;

	if (!cmd->argv[1])
	{
		dir = get_env(cmd->sh->env, "HOME");
		if (!dir)
			ft_error(NULL, "HOME dir not set!", BUILTIN_MISUSE);
	}
	dir = cmd->argv[1];
	if (chdir(cmd->argv[1]))
	{
		ft_error2(cmd->argv[1], strerror(errno), NULL);
		if (cmd->pid == -1)
			free_exec(cmd);
		else
			free_exec_shell(cmd);
		return (GENERAL_ERROR);
	}
	free_exec(cmd);
	return (EXIT_SUCCESS);
}
