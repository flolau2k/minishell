/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:33:33 by flauer            #+#    #+#             */
/*   Updated: 2023/08/29 11:38:49 by flauer           ###   ########.fr       */
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
	a1->pid = pid;
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
