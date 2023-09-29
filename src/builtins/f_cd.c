/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:10:31 by flauer            #+#    #+#             */
/*   Updated: 2023/09/29 14:23:56 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	set_oldpwd(t_exec *cmd, char *oldpwd)
{
	char	*new;
	char	*key;

	new = ft_strjoin("OLDPWD=", oldpwd);
	key = ft_strdup("OLDPWD");
	cmd->sh->env = put_in_env(cmd->sh->env, new, key);
	free(new);
	free(oldpwd);
}

static int	cd_error(t_exec *cmd, char *dir)
{
	char	*errmsg;

	errmsg = strerror(errno);
	if (cmd->pid == -1)
		free_exec(cmd);
	else
		free_exec_shell(cmd);
	return (ft_error2(dir, errmsg, NULL, GENERAL_ERROR));
}

int	f_cd(t_exec *cmd)
{
	char	*dir;
	char	*oldpwd;

	if (num_args(cmd->argv) > 2)
		return (ft_error2("cd", "too many arguments", NULL, GENERAL_ERROR));
	dir = cmd->argv[1];
	if (!cmd->argv[1])
	{
		dir = get_env(cmd->sh->env, "HOME");
		if (!dir)
			return (ft_error2("cd", "HOME dir not set!", NULL, GENERAL_ERROR));
	}
	oldpwd = getcwd(NULL, 0);
	if (chdir(dir))
	{
		free(oldpwd);
		return (cd_error(cmd, dir));
	}
	set_oldpwd(cmd, oldpwd);
	free_exec(cmd);
	return (EXIT_SUCCESS);
}
