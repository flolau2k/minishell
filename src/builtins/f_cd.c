/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:10:31 by flauer            #+#    #+#             */
/*   Updated: 2023/09/29 09:55:31 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	f_cd(t_exec *cmd)
{
	char	*dir;

	dir = cmd->argv[1];
	if (!dir)
	{
		dir = get_env(cmd->sh->env, "HOME");
		if (!dir)
		{
			ft_error2(NULL, "HOME dir not set!", NULL);
			return (GENERAL_ERROR);
		}
	}
	if (chdir(dir))
	{
		ft_error2(dir, strerror(errno), NULL);
		if (cmd->pid == -1)
			free_exec(cmd);
		else
			free_exec_shell(cmd);
		return (GENERAL_ERROR);
	}
	free_exec(cmd);
	return (EXIT_SUCCESS);
}
