/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:22:01 by pcazac            #+#    #+#             */
/*   Updated: 2023/09/29 16:24:02 by flauer           ###   ########.fr       */
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
		{
			pipe->right = (t_cmd *)node;
			return ;
		}
		else
			arrange_redir_tree(&pipe->right, node);
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
		{
			pipe->right = (t_cmd *)node;
			return ;
		}
		else
			arrange_command_tree(&pipe->right, node);
	}
	else if ((*tree)->type == NODE_REDIRECT)
	{
		redir = (t_redir *)*tree;
		while (redir->cmd && redir->cmd->type == NODE_REDIRECT)
			redir = (t_redir *)redir->cmd;
		redir->cmd = (t_cmd *)node;
	}
}

void	print_tree(t_cmd **tree)
{
	t_pipe	*pipe;
	t_redir	*redir;
	t_exec	*exec;


	if ( *tree && (*tree)->type == NODE_PIPE)
	{
		pipe = (t_pipe *)(*tree);
		printf("|||---START PIPE---|||\n");
		printf("Pipe: %p\n", pipe);
		printf("Pipe Type: %i\n", pipe->type);
		if (pipe->left)
		{
			printf("|||---Pipe Left---|||\n");
			printf("Pipe Left: %p\n", pipe->left);
			printf("Pipe Type Left: %i\n", pipe->left->type);
			print_tree(&(pipe->left));
		}
		if (pipe->right)
		{
			printf("|||---Pipe Right---|||\n");
			printf("Pipe Right: %p\n", pipe->right);
			printf("Pipe Type Right: %i\n", pipe->right->type);
			print_tree(&(pipe->right));
		}
		return ;
	}
	else if ( *tree && (*tree)->type == NODE_REDIRECT)
	{
		redir = (t_redir *)(*tree);
		printf("---START REDIRECT---\n");
		printf("Redir Type: %i\n", redir->type);
		printf("Redir Mode: %i\n", redir->mode);
		printf("Exec Arrg: ##%s##\n", redir->file);
		if (redir->cmd)
			print_tree(&(redir->cmd));
		return ;
	}
	else if ( *tree && (*tree)->type == NODE_EXEC)
	{
		exec = (t_exec *)(*tree);
		printf("---START COMMAND---\n");
		printf("Exec Type: %i\n", exec->type);
		printf("Exec Command: %s\n", exec->cmd);
		int	i = -1;
		while(exec->argv[++i])
		{
			printf("Exec Arrg: ##%s##\n", exec->argv[i]);
		}
		return ;
	}
}
