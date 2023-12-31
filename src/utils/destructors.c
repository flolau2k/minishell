/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:13:10 by flauer            #+#    #+#             */
/*   Updated: 2023/10/10 16:41:41 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_tree(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->type == NODE_EXEC)
		free_exec((t_exec *)cmd);
	else if (cmd->type == NODE_PIPE)
		free_pipe((t_pipe *)cmd);
	else if (cmd->type == NODE_REDIRECT)
		free_redir((t_redir *)cmd);
	cmd = NULL;
}

void	free_tree_shell(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free_shell(cmd->sh);
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
	free_arr(arg->argv);
	free(arg);
}

void	free_pipe(t_pipe *arg)
{
	free_tree(arg->left);
	free_tree(arg->right);
	free(arg);
}

void	free_redir(t_redir *arg)
{
	free_tree(arg->cmd);
	free(arg->file);
	free(arg);
}
