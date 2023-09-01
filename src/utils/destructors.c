/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:13:10 by flauer            #+#    #+#             */
/*   Updated: 2023/09/01 13:16:32 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_tree(t_cmd *cmd)
{
	if (cmd->type == NODE_EXEC)
		free_exec((t_exec *)cmd);
	else if (cmd->type == NODE_PIPE)
		free_pipe((t_pipe *)cmd);
	else if (cmd->type == NODE_REDIRECT)
		free_redir((t_redir *)cmd);
	cmd = NULL;
}

void	free_exec(t_exec *arg)
{
	free(arg->argv);
	free(arg->eargv);
	free(arg);
}

void	free_pipe(t_pipe *arg)
{
	if (arg->left)
	{
		free_tree(arg->left);
		arg->left = NULL;
	}
	if (arg->right)
	{
		free_tree(arg->right);
		arg->right = NULL;
	}
	free(arg);
}

void	free_redir(t_redir *arg)
{
	if (arg->cmd)
	{
		free_tree(arg->cmd);
		arg->cmd = NULL;
	}
	free(arg);
}
