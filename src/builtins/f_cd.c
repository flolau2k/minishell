/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:10:31 by flauer            #+#    #+#             */
/*   Updated: 2023/08/31 15:17:31 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	f_cd(t_exec *cmd)
{
	char	*dir;

	// printf("test: %s\n", cmd->cmd);

	if (!cmd->argv[1])
	{
		dir = get_env(cmd->sh->env, "HOME");
		if (!dir)
			ft_error("HOME not set!", GENERAL_ERROR);
	}
	dir = cmd->argv[1];
	chdir(cmd->argv[1]);
}
