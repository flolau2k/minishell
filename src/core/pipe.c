/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:33:33 by flauer            #+#    #+#             */
/*   Updated: 2023/10/12 15:01:13 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_pipe(int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

static void	it_s_a_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

pid_t	create_pipe(void (f1)(t_cmd *), t_cmd *a1, t_cmd *tofree)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		ft_error("pipe", strerror(errno), GENERAL_ERROR);
	pid = fork();
	if (pid == -1)
		ft_error("fork", strerror(errno), GENERAL_ERROR);
	if (pid == 0)
	{
		it_s_a_child();
		dup2(pipe_fd[1], STDOUT_FILENO);
		close_pipe(pipe_fd);
		if (tofree)
			free_tree(tofree);
		a1->pid = pid;
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
	dup2(tty[0], STDIN_FILENO);
	dup2(tty[1], STDOUT_FILENO);
	return (ret);
}

pid_t	execute_command_pipe(char *cmd, char **argv)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		ft_error("pipe", strerror(errno), GENERAL_ERROR);
	pid = fork();
	if (pid == -1)
		ft_error("fork", strerror(errno), GENERAL_ERROR);
	if (pid == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close_pipe(pipe_fd);
		if (execve(cmd, argv, NULL) == -1)
			ft_error(cmd, strerror(errno), GENERAL_ERROR);
	}
	else
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close_pipe(pipe_fd);
	}
	return (pid);
}
