/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:10:31 by flauer            #+#    #+#             */
/*   Updated: 2023/09/29 10:28:49 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_oldpwd(t_exec *cmd, char *oldpwd)
{
	char	*new;
	char	*key;

	new = ft_strjoin("OLDPWD=", oldpwd);
	key = ft_strdup("OLDPWD");
	cmd->sh->env = put_in_env(cmd->sh->env, new, key);
	free(new);
	free(oldpwd);
}

void	cd_error(t_exec *cmd, char *dir)
{
	ft_error2(dir, strerror(errno), NULL);
	if (cmd->pid == -1)
		free_exec(cmd);
	else
		free_exec_shell(cmd);
}

int	f_cd(t_exec *cmd)
{
	char	*dir;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
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
		cd_error(cmd, dir);
		return (GENERAL_ERROR);
	}
	set_oldpwd(cmd, oldpwd);
	free_exec(cmd);
	return (EXIT_SUCCESS);
}
