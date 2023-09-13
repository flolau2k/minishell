/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:13:10 by flauer            #+#    #+#             */
/*   Updated: 2023/09/13 16:14:56 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	free_tree(t_cmd *cmd)
// {
// 	if (!cmd)
// 		return ;
// 	if (cmd->type == NODE_EXEC)
// 		free_exec((t_exec *)cmd);
// 	else if (cmd->type == NODE_PIPE)
// 		free_pipe((t_pipe *)cmd);
// 	else if (cmd->type == NODE_REDIRECT)
// 		free_redir((t_redir *)cmd);
// 	cmd = NULL;
// }

void	free_shell(t_shell *sh)
{
	free_arr(sh->env);
}

void	free_exec(t_exec *arg)
{
	free_arr(arg->argv);
	free(arg->eargv);
	free(arg);
}

void	free_pipe(t_pipe *arg)
{
	free(arg);
}

void	free_redir(t_redir *arg)
{
	free(arg->file);
	free(arg);
}
