/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:28:39 by flauer            #+#    #+#             */
/*   Updated: 2023/08/21 15:22:29 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_from_env(t_astnode *cmd)
{
	
}

void	execute(t_astnode *cmd)
{
	if (ft_strncmp(cmd, "echo", ft_strlen("echo")))
		return (echo(cmd));
	else if (ft_strncmp(cmd, "cd", ft_strlen("cd")))
		return (cd(cmd));
	else if (ft_strncmp(cmd, "env", ft_strlen("env")))
		return (env(cmd));
	else if (ft_strncmp(cmd, "exit", ft_strlen("exit")))
		return (exit(cmd));
	else if (ft_strncmp(cmd, "export", ft_strlen("export")))
		return (export(cmd));
	else if (ft_strncmp(cmd, "pwd", ft_strlen("pwd")))
		return (pwd(cmd));
	else if (ft_strncmp(cmd, "unset", ft_strlen("unset")))
		return (unset(cmd));
	else
		return (exec_from_env(cmd)); //execute cmd from path
}
