/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:22:01 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/12 14:35:17 by pcazac           ###   ########.fr       */
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

void	go_along_pipe(t_cmd **tree, t_cmd *node)
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

void	go_along_redirect(t_cmd **tree, t_redir *node)
{
	t_redir	*redir;

	redir = (t_redir *)*tree;
	if (!redir->cmd)
		redir->cmd = (t_cmd *)node;
	else
		arrange_redir_tree((t_cmd **)&(redir->cmd), node);
}

/// @brief Inserts the redirect node in the AST
/// @param tree AST Root node
/// @param node New node to be added
void	arrange_redir_tree(t_cmd **tree, t_redir *node)
{
	if (!(*tree))
	{
		*tree = (t_cmd *)node;
		return ;
	}
	if ((*tree)->type == NODE_PIPE)
		go_along_pipe(tree, (t_cmd *)node);
	else if ((*tree)->type == NODE_REDIRECT)
		go_along_redirect(tree, node);
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
		go_along_pipe(tree, (t_cmd *)node);
	else if ((*tree)->type == NODE_REDIRECT)
	{
		redir = (t_redir *)*tree;
		while (redir->cmd && redir->cmd->type == NODE_REDIRECT)
			redir = (t_redir *)redir->cmd;
		redir->cmd = (t_cmd *)node;
	}
}
