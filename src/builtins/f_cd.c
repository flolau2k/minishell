/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:10:31 by flauer            #+#    #+#             */
/*   Updated: 2023/08/25 19:05:27 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	f_cd(t_exec *cmd)
{
	// char	*dir;

	printf("test: %s\n", cmd->cmd);

	// if (!cmd->argv[1])
	// {
	// 	dir = get_env(cmd->sh->env, "HOME");
	// 	if (!dir)
	// 		printf("HOME not set!", GENERAL_ERROR); //TODO: set return code to 1
	// }
	// dir = cmd->argv[1];
	// chdir(cmd->argv[1]);
	return (0);
}
