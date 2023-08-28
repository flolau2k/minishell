/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:28:39 by flauer            #+#    #+#             */
/*   Updated: 2023/08/28 18:02:52 by flauer           ###   ########.fr       */
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
	&f_echo,
	&f_cd,
	&f_env,
	&f_exit,
	&f_export,
	&f_pwd,
	&f_unset
};

fcn_p	get_builtin(t_exec *exec)
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

int	execute(t_cmd *cmd)
{
	t_exec		*exec;
	fcn_p		fcn;
	pid_t		pid;

	if (cmd->type == NODE_EXEC)
	{
		exec = (t_exec *)cmd;
		fcn = get_builtin(exec);
		if (fcn)
			return (fcn(exec));
	}
	pid = fork();
	if (pid == -1)
		ft_error("fork", GENERAL_ERROR);
	if (pid == 0)
	{
		
	}
	return (exec_rec(cmd));
}

int	exec_rec(t_cmd *cmd)
{
	if (cmd->type == NODE_EXEC)
		return (do_exec((t_exec *)cmd));
	else if (cmd->type == NODE_PIPE)
		return (do_pipe((t_pipe *)cmd));
	else if (cmd->type == NODE_REDIRECT)
		return (do_redir((t_redir *)cmd));
}

// int	do_pipe(t_pipe *cmd)
// {
// 	int	fd[2];
// 	int	pid;

// 	if (pipe(fd) == -1)
// 		ft_error(NULL, GENERAL_ERROR);
// 	pid = fork();
// 	if (pid == -1)
// 		ft_error(strerror(errno), GENERAL_ERROR);
// 	if (pid == 0)
// 	{
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		return (execute(cmd->left));
// 	}
// 	else
// 	{
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		return (execute(cmd->right));
// 	}
// }

int	do_pipe(t_pipe *cmd)
{
	pid_t	pid;

	pid = create_pipe(&execute, cmd->left);
	if (pid == 0)
		exit(0);
	
}

int	do_redir(t_redir *redir)
{
	if (redir->mode & O_HEREDOC)
	{
		
	}
	redir->fd = open(redir->file, redir->mode);
	if (redir->fd == -1)
		ft_error(strerror(errno), GENERAL_ERROR);
	if (redir->mode & O_WRONLY)
		dup2(redir->fd, STDOUT_FILENO);
	else
		dup2(redir->fd, STDIN_FILENO);
	close(redir->fd);
	return (execute(redir->cmd));
}

void	do_execve(t_exec *exec)
{
	char	*cmd;
	char	*cmd_msg;

	cmd = get_cmd(exec->cmd, exec->sh->env);
	if (!cmd)
	{
		printf("minishell: %s: command not found!", exec->cmd);
		exit(GENERAL_ERROR);
	}
	if (execve(exec->cmd, exec->argv, exec->sh->env) == -1)
	{
		printf("minishell: %s: %s", cmd, strerror(errno));
		exit(GENERAL_ERROR);
	}
}

/// @brief Execute exec node. checking first, if command is a builtin, and
/// then forwards to the do_execve function
/// @param exec Node to execute
int	do_exec(t_exec *exec)
{
	int	i;
	int	pid;
	int	stat_loc;

	i = 0;
	
	pid = fork();
	if (pid == 0)
		do_execve(exec);
	waitpid(pid, &stat_loc, 0);
	return (WEXITSTATUS(stat_loc));
}
