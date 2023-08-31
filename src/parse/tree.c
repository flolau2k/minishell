/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:22:01 by pcazac            #+#    #+#             */
/*   Updated: 2023/08/31 10:49:09 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/// @brief Inserts the pipe node in the AST
/// @param tree AST Root node
/// @param node New node to be added
void	arrange_pipe_tree(t_cmd **tree, t_pipe *node)
{
	t_pipe	*pipe;

	if (!(*tree))
	{
		*tree = (t_cmd *)node;
		return ;
	}
	else if ((*tree)->type == NODE_REDIRECT || (*tree)->type == NODE_EXEC)
	{
		node->left = (*tree);
		*tree = (t_cmd *)node;
	}
	else if ((*tree)->type == NODE_PIPE)
	{
		pipe = (t_pipe *)*tree;
		if (pipe->right)
			arrange_pipe_tree(&(pipe->right), node); 
		else if (!pipe->right)
			pipe->right = (t_cmd *)node;
	}
}

/// @brief Inserts the redirect node in the AST
/// @param tree AST Root node
/// @param node New node to be added
void	arrange_redir_tree(t_cmd **tree, t_redir *node)
{
	t_pipe	*pipe;
	t_cmd	*temp;
	t_redir	*redir;

	if (!(*tree))
	{
		*tree = (t_cmd *)node;
		return ;
	}
	if ((*tree)->type == NODE_PIPE)
	{
		pipe = (t_pipe *)*tree;
		if (!pipe->right)
			pipe->right = (t_cmd *)node;
		else
		{
			temp = pipe->right;
			pipe->right = (t_cmd *)node;
			node->cmd = temp;
		}
	}
	else if ((*tree)->type == NODE_REDIRECT)
	{
		redir = (t_redir *)*tree;
		if (!redir->cmd)
			redir->cmd = (t_cmd *)node;
		else
		{
			temp = *tree;
			*tree = (t_cmd *)node;
			node->cmd = temp;
		}
	}
	else if ((*tree)->type == NODE_EXEC)
	{
		temp = *tree;
		*tree = (t_cmd *)node;
		node->cmd = temp;
	}
}

/// @brief Inserts the command node in the AST
/// @param tree AST Root node
/// @param node New node to be added
void	arrange_command_tree(t_cmd **tree, t_exec *node)
{
	t_redir	*redir;
	t_pipe	*pipe;

	if (!tree || !node)
		return ;
	if (!(*tree))
	{
		*tree = (t_cmd *)node;
		return ;
	}
	if ((*tree)->type == NODE_PIPE)
	{
		pipe = (t_pipe *)*tree;
		if (!pipe->right)
			pipe->right = (t_cmd *)node;
		else if (pipe->right->type == NODE_REDIRECT)
		{
			redir = (t_redir *)pipe->right;
			while (redir->cmd && redir->cmd->type == NODE_REDIRECT)
				redir = (t_redir *)redir->cmd;
			if (redir) // Useless condition
				redir->cmd = (t_cmd *)node;
		}
	}
	else if ((*tree)->type == NODE_REDIRECT)
	{
		redir = (t_redir *)*tree;
		while (redir && redir->cmd)
			redir = (t_redir *)redir->cmd;
		if (redir)
			redir->cmd = (t_cmd *)node;
	}
}
