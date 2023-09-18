/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_alloc_destructors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:13:10 by flauer            #+#    #+#             */
/*   Updated: 2023/09/17 01:47:49 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_init_exec(t_exec *arg)
{
	free(arg->argv);
	arg->argv = NULL;
	free(arg);
}

void	free_init_pipe(t_pipe *arg)
{
	if (arg->left)
	{
		free_init_tree(arg->left);
		arg->left = NULL;
	}
	if (arg->right)
	{
		free_init_tree(arg->right);
		arg->right = NULL;
	}
	free(arg);
}

void	free_init_redir(t_redir *arg)
{
	if (arg->cmd)
	{
		free_init_tree(arg->cmd);
		arg->cmd = NULL;
	}
	free(arg);
}

void	free_init_tree(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->type == NODE_EXEC)
		free_init_exec((t_exec *)cmd);
	else if (cmd->type == NODE_PIPE)
		free_init_pipe((t_pipe *)cmd);
	else if (cmd->type == NODE_REDIRECT)
		free_init_redir((t_redir *)cmd);
	cmd = NULL;
}
