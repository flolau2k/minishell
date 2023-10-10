/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:10:31 by flauer            #+#    #+#             */
/*   Updated: 2023/10/10 16:07:23 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	set_oldpwd(t_exec *cmd, char *oldpwd)
{
	char	*new;
	char	*key;
	char	*cwd[2];

	new = ft_strjoin("OLDPWD=", oldpwd);
	key = ft_strdup("OLDPWD");
	cmd->sh->env = put_in_env(cmd->sh->env, new, key);
	cwd[0] = getcwd(NULL, 0);
	cwd[1] = ft_strjoin("PWD=", cwd[0]);
	free(new);
	free(oldpwd);
	replace_in_env(cmd->sh->env, cwd[1]);
	free(cwd[0]);
	free(cwd[1]);
}

static int	cd_error(t_exec *cmd, char *msg, char *errmsg)
{
	if (cmd->pid == -1)
		free_exec(cmd);
	else
		free_exec_shell(cmd);
	return (ft_error2(msg, errmsg, NULL, GENERAL_ERROR));
}

int	f_cd(t_exec *cmd)
{
	char	*dir;
	char	*oldpwd;

	dir = cmd->argv[1];
	if (!cmd->argv[1])
	{
		dir = get_env(cmd->sh->env, "HOME");
		if (!dir)
			return (cd_error(cmd, "cd", "HOME dir not set!"));
	}
	oldpwd = getcwd(NULL, 0);
	if (chdir(dir))
	{
		free(oldpwd);
		return (cd_error(cmd, dir, strerror(errno)));
	}
	set_oldpwd(cmd, oldpwd);
	free_exec(cmd);
	return (EXIT_SUCCESS);
}
