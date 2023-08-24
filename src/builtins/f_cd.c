/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:10:31 by flauer            #+#    #+#             */
/*   Updated: 2023/08/22 15:58:21 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	f_cd(t_exec *cmd)
{
	char	*dir;

	if (!cmd->argv[1])
	{
		dir = get_env(cmd->env, "HOME");
		if (!dir)
			// HOME not set!
	}
	dir = cmd->argv[1];
	chdir(cmd->argv[1]);
}
