/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:33:33 by flauer            #+#    #+#             */
/*   Updated: 2023/09/14 15:40:52 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_pipe(int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

pid_t	create_pipe(void (f1)(t_cmd *), t_cmd *a1, t_cmd *tofree)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (f1 && a1->type == NODE_PIPE)
		ft_error2("Pipe in child!!\n", 1);
	if (pipe(pipe_fd) == -1)
		ft_error("pipe", GENERAL_ERROR);
	pid = fork();
	if (pid == -1)
		ft_error("fork", GENERAL_ERROR);
	if (pid == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close_pipe(pipe_fd);
		if (tofree)
			free_tree(tofree);
		if (f1)
			f1(a1);
	}
	else
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close_pipe(pipe_fd);
	}
	return (pid);
}

char	*execute_command(char *cmd, char **argv)
{
	pid_t	pid;
	int		stat_loc;
	int		tty[2];
	char	*ret;

	tty[0] = dup(STDIN_FILENO);
	tty[1] = dup(STDOUT_FILENO);
	pid = execute_command_pipe(cmd, argv);
	waitpid(pid, &stat_loc, 0);
	if (WEXITSTATUS(stat_loc) == 0)
	{
		ret = get_next_line(STDIN_FILENO);
		ret = ft_strtrim(ret, "\n");
	}
	else
		ret = NULL;
	dup2(tty[0],STDIN_FILENO);
	dup2(tty[1], STDOUT_FILENO);
	return (ret);
}

pid_t	execute_command_pipe(char *cmd, char **argv)
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
		close_pipe(pipe_fd);
		if (execve(cmd, argv, NULL) == -1)
		{
			printf("minishell: %s: %s\n", cmd, strerror(errno));
			exit(GENERAL_ERROR);
		}
	}
	else
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close_pipe(pipe_fd);
	}
	return (pid);
}
