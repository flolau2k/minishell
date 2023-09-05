/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:33:33 by flauer            #+#    #+#             */
/*   Updated: 2023/09/05 14:54:20 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

pid_t	create_pipe(void (f1)(t_cmd *), t_cmd *a1)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		ft_error("pipe", GENERAL_ERROR);
	pid = fork();
	if (pid == -1)
		ft_error("fork", GENERAL_ERROR);
	if (pid == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		if (f1)
			f1(a1);
	}
	else
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	return (pid);
}

t_exec	*create_exec_node(char	*cmd)
{
	t_exec *ret;

	ret = malloc(sizeof(t_exec));
	if (!ret)
		ft_error("malloc error!", GENERAL_ERROR);
	ret->type = NODE_EXEC;
	ret->cmd = cmd;
	ret->argv = ft_calloc(2, sizeof(char *));
	if (!ret->argv)
		ft_error("malloc error!", GENERAL_ERROR);
	ret->argv[0] = cmd;
	ret->eargv = NULL;
	ret->sh = NULL;
	return (ret);
}

char	*execute_command(char *cmd)
{
	char	*ret;
	pid_t	pid;
	t_cmd	*tree;

	tree = (t_cmd *)create_exec_node(cmd);
	pid = create_pipe(&rec_execute, tree);
	waitpid(pid, NULL, 0);
	ret = get_next_line(STDIN_FILENO);
	free(((t_exec *)tree)->argv);
	free((t_exec *)tree);
	return (ret);
}
