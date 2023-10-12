/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:14:37 by flauer            #+#    #+#             */
/*   Updated: 2023/10/12 13:44:17 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_file(char *name)
{
	bool	ret;
	t_stat	statbuf;

	if (stat(name, &statbuf) != 0)
		return (0);
	ret = S_ISDIR(statbuf.st_mode);
	return (!ret);
}

void	do_builtin(t_fcn_p fcn, t_exec *exec)
{
	int		ret;
	t_shell	*sh;

	sh = exec->sh;
	ret = fcn(exec);
	sh->ret = ret;
}

void	exec_error(t_exec *exec, char *msg, char *error, int exitcode)
{
	ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", msg, error);
	free_shell(exec->sh);
	free_exec(exec);
	exit(exitcode);
}
