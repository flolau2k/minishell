/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:28:39 by flauer            #+#    #+#             */
/*   Updated: 2023/08/29 11:36:37 by flauer           ###   ########.fr       */
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
		here_doc(redir->file);
	else
	{
		redir->fd = open(redir->file, redir->mode);
		if (redir->fd == -1)
			ft_error(strerror(errno), GENERAL_ERROR);
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
		set_shell_ret(WEXITSTATUS(stat_loc)); // set last return code!
	}
}
