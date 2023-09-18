/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:10:31 by flauer            #+#    #+#             */
/*   Updated: 2023/09/15 11:29:15 by flauer           ###   ########.fr       */
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
			ft_error(NULL, "HOME dir not set!", GENERAL_ERROR);
	}
	dir = cmd->argv[1];
	chdir(cmd->argv[1]);
	free_exec(cmd);
	return (EXIT_SUCCESS);
}
