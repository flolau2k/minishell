/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:28:39 by flauer            #+#    #+#             */
/*   Updated: 2023/09/22 16:19:31 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	rec_execute(t_cmd *cmd)
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
	t_cmd	*left;
	t_cmd	*right;

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
	cmd->pid = redir->pid;
	if (redir->mode & O_HEREDOC)
		here_doc(redir);
	else
	{
		redir->fd = open(redir->file, redir->mode, 0644);
		if (redir->fd == -1)
		{
			dup2(STDERR_FILENO, STDOUT_FILENO);
			printf("minishell: %s: %s\n", redir->file, strerror(errno));
			free_tree_shell((t_cmd *)redir);
			exit(GENERAL_ERROR);
		}
		if (redir->mode & O_WRONLY)
			dup2(redir->fd, STDOUT_FILENO);
		else
			dup2(redir->fd, STDIN_FILENO);
		close(redir->fd);
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
		return (do_builtin(fcn, exec));
	cmd = get_cmd(exec->cmd, exec->sh->env);
	if (!cmd)
		exec_error(exec, "command not found!", exec->cmd);
	if (execve(cmd, exec->argv, exec->sh->env) == -1)
		exec_error(exec, cmd, strerror(errno));
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
