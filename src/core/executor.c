/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:28:39 by flauer            #+#    #+#             */
/*   Updated: 2023/09/13 17:04:31 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute(t_cmd *cmd)
{
	t_fcn_p	fcn;
	pid_t	pid;
	int		stat_loc;

	if (!cmd)
		return (0);
	if (cmd->type == NODE_EXEC)
	{
		fcn = get_builtin((t_exec *)cmd);
		if (fcn)
			return (fcn((t_exec *)cmd));
	}
	pid = fork();
	if (pid == -1)
	{
		free_tree(cmd);
		printf("minishell: fork: %s\n", strerror(errno));
		exit(GENERAL_ERROR);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		rec_execute(cmd);
	}
	free_tree(cmd);
	waitpid(pid, &stat_loc, 0);
	return (WEXITSTATUS(stat_loc));
}

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
	t_cmd	*left;
	t_cmd	*right;

	left = cmd->left;
	right = cmd->right;
	free_pipe_single(cmd);
	create_pipe(&rec_execute, left, right);
	free_tree(left);
	rec_execute(right);
}

void	do_redir(t_redir *redir)
{
	if (redir->mode & O_HEREDOC)
		here_doc(redir);
	else
	{
		redir->fd = open(redir->file, redir->mode, 0644);
		if (redir->fd == -1)
		{
			printf("minishell: %s: %s\n", redir->file, strerror(errno));
			free_redir(redir);
			exit(GENERAL_ERROR);
		}
		if (redir->mode & O_WRONLY)
			dup2(redir->fd, STDOUT_FILENO);
		else
			dup2(redir->fd, STDIN_FILENO);
		close(redir->fd);
	}
	free_redir_single(redir);
	return (rec_execute(redir->cmd));
}

void	do_exec(t_exec *exec)
{
	char	*cmd;
	t_fcn_p	fcn;

	fcn = get_builtin(exec);
		if (fcn)
			exit(fcn(exec));
	cmd = get_cmd(exec->cmd, exec->sh->env);
	if (!cmd)
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		printf("minishell: %s: command not found!\n", exec->cmd);
		free_exec(exec);
		exit(GENERAL_ERROR);
	}
	if (execve(cmd, exec->argv, exec->sh->env) == -1)
	{
		//  Must free memory if execve fails ???
		dup2(STDERR_FILENO, STDOUT_FILENO);
		printf("minishell: %s: %s\n", cmd, strerror(errno));
		free_exec(exec);
		exit(GENERAL_ERROR);
	}
}
