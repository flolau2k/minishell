/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:10:33 by flauer            #+#    #+#             */
/*   Updated: 2023/08/29 15:44:19 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	f_export(t_exec *cmd)
{
	char	**new_env;

	if (!cmd->argv[1])
		f_env(cmd);
	new_env = set_env(cmd->sh->env, cmd->argv[1]);
}
