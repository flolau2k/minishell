/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:22:01 by pcazac            #+#    #+#             */
/*   Updated: 2023/08/29 14:06:22 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	arrange_pipe_tree(t_cmd **tree, t_pipe *node)
{
	t_pipe	*pipe;

	if (!(*tree))
	{
		*tree = (t_cmd *)node;
		return ;
	}
	pipe = (t_pipe *)*tree;
	if (pipe->right)
		arrange_pipe_tree(&(pipe->right), node); 
	else
		pipe->right = (t_cmd *)node;
}

void	arrange_redir_tree(t_cmd **tree, t_redir *node)
{
	t_pipe	*pipe;
	t_cmd	*temp;

	if (!(*tree))
	{
		*tree = (t_cmd *)node;
		return ;
	}
	if ((*tree)->type == NODE_PIPE)
	{
		pipe = (t_pipe *)*tree;
		if (!pipe->left)
			pipe->left = (t_cmd *)node;
		else
		{
			temp = pipe->left;
			pipe->left = (t_cmd *)node;
			node->cmd = temp;
		}
	}
}

void	arrange_command_tree(t_cmd **tree, t_exec *node)
{
	t_redir	*redir;
	t_pipe	*pipe;

	if (!(*tree))
	{
		*tree = (t_cmd *)node;
		return ;
	}
	if ((*tree)->type == NODE_PIPE)
	{
		pipe = (t_pipe *)*tree;
		if (!pipe->left)
		{
			pipe->left = (t_cmd *)node;
			return ;
		}
		else
		{
			redir = (t_redir *)pipe->left;
			while (redir->cmd)
				redir = (t_redir *)redir->cmd; 
			redir->cmd = (t_cmd *)node;
		}
	}
	else if ((*tree)->type == NODE_REDIRECT)
	{
		redir = (t_redir *)*tree;
		while (redir->cmd)
			redir = (t_redir *)redir->cmd; 
		redir->cmd = (t_cmd *)node;
	}
}