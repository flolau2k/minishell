/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:28:39 by flauer            #+#    #+#             */
/*   Updated: 2023/08/22 12:16:42 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute(t_cmd *cmd)
{
	if (cmd->type == NODE_EXEC)
		return (do_exec((t_exec *)cmd));
	else if (cmd->type == NODE_PIPE)
		return (do_pipe((t_pipe *)cmd));
	else if (cmd->type == NODE_REDIRECT)
		return (do_redir((t_redir *)cmd));
}

void	do_pipe(t_pipe *cmd)
{

}

void	do_exec(t_exec *exec)
{
	char	**fcns;
	

	fcns = (char *[]){"echo", "cd", "env", "exit", "export",
		"pwd", "unset", NULL};

}

void	do_redir(t_redir *redir)
{
	
}

// void	execute(t_cmd *cmd)
// {
// 	if (ft_strncmp(cmd, "echo", ft_strlen("echo")))
// 		return (echo(cmd));
// 	else if (ft_strncmp(cmd, "cd", ft_strlen("cd")))
// 		return (cd(cmd));
// 	else if (ft_strncmp(cmd, "env", ft_strlen("env")))
// 		return (env(cmd));
// 	else if (ft_strncmp(cmd, "exit", ft_strlen("exit")))
// 		return (exit(cmd));
// 	else if (ft_strncmp(cmd, "export", ft_strlen("export")))
// 		return (export(cmd));
// 	else if (ft_strncmp(cmd, "pwd", ft_strlen("pwd")))
// 		return (pwd(cmd));
// 	else if (ft_strncmp(cmd, "unset", ft_strlen("unset")))
// 		return (unset(cmd));
// 	else
// 		return (exec_from_env(cmd)); //execute cmd from path
// }
