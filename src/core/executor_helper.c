/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:14:37 by flauer            #+#    #+#             */
/*   Updated: 2023/09/15 11:14:56 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	do_builtin(t_fcn_p fcn, t_exec *exec)
{
	int		ret;
	t_shell	*sh;

	sh = exec->sh;
	ret = fcn(exec);
	sh->ret = ret;
}

void	exec_error(t_exec *exec, char *msg, char *error)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("minishell: %s: %s\n", msg, error);
	free_shell(exec->sh);
	free_exec(exec);
	exit(GENERAL_ERROR);
}
