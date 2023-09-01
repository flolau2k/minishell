/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:28:39 by flauer            #+#    #+#             */
/*   Updated: 2023/09/01 12:21:12 by flauer           ###   ########.fr       */
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

static const t_fcn_p	g_fcn_p[] = {
	(t_fcn_p)&f_echo,
	(t_fcn_p)&f_cd,
	(t_fcn_p)&f_env,
	(t_fcn_p)&f_exit,
	(t_fcn_p)&f_export,
	(t_fcn_p)&f_pwd,
	(t_fcn_p)&f_unset
};

static t_fcn_p	get_builtin(t_exec *exec)
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
	t_fcn_p	fcn;
	pid_t	pid;
	int		stat_loc;

	if (cmd->type == NODE_EXEC)
	{
		fcn = get_builtin((t_exec *)cmd);
		if (fcn)
			return (fcn((t_exec *)cmd));
	}
	pid = fork();
	if (pid == -1)
	{
		printf("minishell: fork: %s\n", strerror(errno));
		exit(GENERAL_ERROR);
	}
	if (pid == 0)
		rec_execute(cmd);
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
	pid_t	pid;

	pid = create_pipe(&rec_execute, cmd->left);
	rec_execute(cmd->right);
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
			exit(GENERAL_ERROR);
		}
		if (redir->mode & O_WRONLY)
			dup2(redir->fd, STDOUT_FILENO);
		else
			dup2(redir->fd, STDIN_FILENO);
		close(redir->fd);
	}
	return (rec_execute(redir->cmd));
}

void	do_exec(t_exec *exec)
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
		printf("minishell: %s: %s\n", cmd, strerror(errno));
		exit(GENERAL_ERROR);
	}
}
