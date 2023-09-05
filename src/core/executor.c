/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:28:39 by flauer            #+#    #+#             */
/*   Updated: 2023/09/04 16:50:46 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static const char	*g_fcn_n[] = {
	"echo",
	"cd",
	"env",
	"exit",
	"export",
	"pwd",
	"unset"
};

static const fcn_p	g_fcn_p[] = {
	(fcn_p)&f_echo,
	(fcn_p)&f_cd,
	(fcn_p)&f_env,
	(fcn_p)&f_exit,
	(fcn_p)&f_export,
	(fcn_p)&f_pwd,
	(fcn_p)&f_unset
};

static fcn_p	get_builtin(t_exec *exec)
{
	int	i;

	i = 0;
	while (g_fcn_n[i])
	{
		if (ft_strncmp(g_fcn_n[i], exec->cmd, ft_strlen(g_fcn_n[i])) == 0)
			return (g_fcn_p[i]);
		i++;
	}
	return (NULL);
}

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
	pid_t	pid;

	pid = create_pipe(&execute, cmd->left);
	cmd->right->pid = pid;
	execute(cmd->right);
}

void	do_redir(t_redir *redir)
{
	redir->cmd->pid = redir->pid;
	if (redir->mode & O_HEREDOC)
		here_doc(redir);
	else
	{
		redir->fd = open(redir->file, redir->mode, 0644);
		if (redir->fd == -1)
		{
			printf("minishell: %s: %s\n", redir->file, strerror(errno));
			exit(GENERAL_ERROR);
		}
		if (redir->mode & O_WRONLY)
			dup2(redir->fd, STDOUT_FILENO);
		else
			dup2(redir->fd, STDIN_FILENO);
		close(redir->fd);
	}
	return (execute(redir->cmd));
}

void	do_execve(t_exec *exec)
{
	char	*cmd;

	cmd = get_cmd(exec->cmd, exec->sh->env);
	if (!cmd)
	{
		printf("minishell: %s: command not found!\n", exec->cmd);
		exit(GENERAL_ERROR);
	}
	if (execve(cmd, exec->argv, exec->sh->env) == -1)
	{
		//  Must free memory if execve fails ???
		printf("minishell: %s: %s\n", cmd, strerror(errno));
		exit(GENERAL_ERROR);
	}
}

/// @brief Execute exec node.
/// @param exec Node to execute
void	do_exec(t_exec *exec)
{
	int		stat_loc;
	pid_t	npid;
	fcn_p	fcn;
	
	if (exec->pid == 0)
		do_execve(exec);
	fcn = get_builtin(exec);
	if (fcn)
		return (fcn(exec));
	else
	{
		npid = fork();
		if (npid == 0)
			do_execve(exec);
		waitpid(npid, &stat_loc, 0);
		exec->sh->ret = WEXITSTATUS(stat_loc);
		close(STDIN_FILENO);
		wait_exit();
	}
}
