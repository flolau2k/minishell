/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:28:39 by flauer            #+#    #+#             */
/*   Updated: 2023/08/24 17:32:16 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_builtin(t_exec *exec)
{
	char	**fcn_n;
	int		i;

	fcn_n = (char *[]){"echo", "cd", "env", "exit", "export", "pwd", 
		"unset", NULL};
	while (fcn_n[i])
	{
		if (ft_strncmp(fcn_n[i], exec->cmd, ft_strlen(fcn_n[i])) == 0)
			return (true);
		i++;
	}
	return (false);
}

void	execute(t_cmd *cmd)
{
	if (cmd->type == NODE_EXEC)
	{
		if (is_builtin((t_exec *)cmd))
			
		return (do_exec((t_exec *)cmd));
	}
	else if (cmd->type == NODE_PIPE)
		return (do_pipe((t_pipe *)cmd));
	else if (cmd->type == NODE_REDIRECT)
		return (do_redir((t_redir *)cmd));
}

void	do_pipe(t_pipe *cmd)
{

}

void	do_redir(t_redir *redir)
{
	
}

void	do_execve(t_exec *exec)
{
	int	pid;
	int	stat_loc;

	pid = fork();
	if (pid == 0)
		execve(exec->cmd, exec->argv, exec->sh->env);
	else
		waitpid(pid, stat_loc, 0);
}

/// @brief Execute exec node. checking first, if command is a builtin, and
/// then forwards to the do_execve function
/// @param exec Node to execute
void	do_exec(t_exec *exec)
{
	char	**fcn_n;
	void	(**fcn_p)(t_exec *);
	int		i;

	fcn_n = (char *[]){"echo", "cd", "env", "exit", "export", "pwd",
		"unset", NULL};
	fcn_p = (void *[]){f_echo, f_cd, f_env, f_exit, f_export, f_pwd,
		f_unset, NULL};
	while (fcn_n[i])
	{
		if (ft_strncmp(fcn_n[i], exec->cmd, ft_strlen(fcn_n[i])) == 0)
			return ((*fcn_p[i])(exec));
		i++;
	}
	return (do_execve(exec));
}
