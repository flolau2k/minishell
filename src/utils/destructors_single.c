/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors_single.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:41:36 by flauer            #+#    #+#             */
/*   Updated: 2023/09/13 16:42:03 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_shell(t_shell *sh)
{
	free_arr(sh->env);
}

void	free_exec_single(t_exec *arg)
{
	free_arr(arg->argv);
	free(arg->eargv);
	free(arg);
}

void	free_pipe_single(t_pipe *arg)
{
	free(arg);
}

void	free_redir_single(t_redir *arg)
{
	free(arg->file);
	free(arg);
}