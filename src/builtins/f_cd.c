/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:10:31 by flauer            #+#    #+#             */
/*   Updated: 2023/08/29 16:13:19 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	f_cd(t_exec *cmd)
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
}
