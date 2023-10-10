/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:28:39 by flauer            #+#    #+#             */
/*   Updated: 2023/10/10 16:51:35 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	rec_execute(t_cmd *cmd)
{
	if (!cmd)
		return ;
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
	t_cmd	*left;
	t_cmd	*right;

	pid = -1;
	left = cmd->left;
	right = cmd->right;
	free_pipe_single(cmd);
	pid = create_pipe(&rec_execute, left, right);
	free_tree(left);
	right->pid = pid;
	return (rec_execute(right));
}

void	do_redir(t_redir *redir)
{
	t_cmd	*cmd;

	cmd = redir->cmd;
	if (cmd)
		cmd->pid = redir->pid;
	redir->fd = open(redir->file, redir->mode, 0644);
	if (redir->fd == -1)
	{
		ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n",
			redir->file, strerror(errno));
		free_tree_shell((t_cmd *)redir);
		exit(GENERAL_ERROR);
	}
	if (redir->mode & O_WRONLY)
		dup2(redir->fd, STDOUT_FILENO);
	else
		dup2(redir->fd, STDIN_FILENO);
	close(redir->fd);
	if (!cmd)
	{
		free_tree_shell((t_cmd *)redir);
		exit(GENERAL_ERROR);
	}
	free_redir_single(redir);
	return (rec_execute(cmd));
}

void	do_execve(t_exec *exec)
{
	char	*cmd;
	t_fcn_p	fcn;

	fcn = get_builtin(exec);
	if (fcn)
	{
		do_builtin(fcn, exec);
		exit(EXIT_SUCCESS);
	}
	cmd = get_cmd(exec->cmd, exec->sh->env);
	if (!cmd)
		exec_error(exec, "command not found", exec->cmd, CMD_NOT_FOUND);
	if (execve(cmd, exec->argv, exec->sh->env) == -1)
		exec_error(exec, cmd, strerror(errno), CMD_ERROR);
}

/// @brief Execute exec node.
/// @param exec Node to execute
void	do_exec(t_exec *exec)
{
	int		stat_loc;
	pid_t	npid;
	t_fcn_p	fcn;

	fcn = get_builtin(exec);
	if (fcn && exec->pid == -1)
		return (do_builtin(fcn, exec));
	if (exec->pid == 0)
		do_execve(exec);
	else
	{
		npid = fork();
		if (npid == 0)
		{
			signal(SIGINT, SIG_DFL);
			do_execve(exec);
		}
		waitpid(npid, &stat_loc, 0);
		exec->sh->ret = WEXITSTATUS(stat_loc);
		close(STDIN_FILENO);
		free_exec(exec);
		wait_exit();
	}
}
