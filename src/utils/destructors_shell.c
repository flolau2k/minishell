/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors_shell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:24:43 by flauer            #+#    #+#             */
/*   Updated: 2023/09/14 13:28:48 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_tree_shell(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->type == NODE_EXEC)
		free_exec_shell((t_exec *)cmd);
	else if (cmd->type == NODE_PIPE)
		free_pipe_shell((t_pipe *)cmd);
	else if (cmd->type == NODE_REDIRECT)
		free_redir_shell((t_redir *)cmd);
	cmd = NULL;
}

void	free_exec_shell(t_exec *arg)
{
	free_arr(arg->argv);
	free(arg->eargv);
	free_shell(arg->sh);
	free(arg);
}

void	free_pipe_shell(t_pipe *arg)
{
	if (arg->left)
	{
		free_tree_shell(arg->left);
		arg->left = NULL;
	}
	if (arg->right)
	{
		free_tree_shell(arg->right);
		arg->right = NULL;
	}
	free(arg);
}

void	free_redir_shell(t_redir *arg)
{
	if (arg->cmd)
	{
		free_tree_shell(arg->cmd);
		arg->cmd = NULL;
		free(arg->file);
	}
	free(arg);
}