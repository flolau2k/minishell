/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:22:01 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/10 13:36:11 by pcazac           ###   ########.fr       */
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
	if ((*tree)->type == NODE_PIPE)
	{
		pipe = (t_pipe *)*tree;
		if (pipe->right)
			arrange_pipe_tree(&(pipe->right), node);
		else if (!pipe->right)
			pipe->right = (t_cmd *)node;
	}
	if ((*tree)->type == NODE_REDIRECT || (*tree)->type == NODE_EXEC)
	{
		node->left = (*tree);
		*tree = (t_cmd *)node;
	}
}

void	arrange_node_pipe(t_cmd **tree, t_cmd *node)
{
	t_pipe	*pipe;

	pipe = (t_pipe *)*tree;
	if (!pipe->right)
	{
		pipe->right = (t_cmd *)node;
		return ;
	}
	else if (node->type == NODE_REDIRECT)
		arrange_redir_tree(&pipe->right, (t_redir *)node);
	else if (node->type == NODE_EXEC)
		arrange_command_tree(&pipe->right, (t_exec *)node);
}

void	arrange_node_redirect(t_cmd **tree, t_redir *node)
{
	t_redir	*redir;
	t_cmd	*temp;

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

/// @brief Inserts the redirect node in the AST
/// @param tree AST Root node
/// @param node New node to be added
void	arrange_redir_tree(t_cmd **tree, t_redir *node)
{
	t_cmd	*temp;

	if (!(*tree))
	{
		*tree = (t_cmd *)node;
		return ;
	}
	if ((*tree)->type == NODE_PIPE)
		arrange_node_pipe(tree, (t_cmd *)node);
	else if ((*tree)->type == NODE_REDIRECT)
		arrange_node_redirect(tree, node);
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

	if (!tree || !node)
		return ;
	if (!(*tree))
	{
		*tree = (t_cmd *)node;
		return ;
	}
	if ((*tree)->type == NODE_PIPE)
		arrange_node_pipe(tree, (t_cmd *)node);
	else if ((*tree)->type == NODE_REDIRECT)
	{
		redir = (t_redir *)*tree;
		while (redir->cmd && redir->cmd->type == NODE_REDIRECT)
			redir = (t_redir *)redir->cmd;
		redir->cmd = (t_cmd *)node;
	}
}
