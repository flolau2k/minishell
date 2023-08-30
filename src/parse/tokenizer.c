/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:02:40 by pcazac            #+#    #+#             */
/*   Updated: 2023/08/30 18:15:16 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_tree(t_cmd **tree)
{
	t_pipe	*pipe;
	t_redir	*redir;
	t_exec	*exec;


	if ( *tree && (*tree)->type == NODE_PIPE)
	{
		pipe = (t_pipe *)(*tree);
		printf("Pipe: %p\n", pipe);
		printf("Pipe Type %i\n", pipe->type);
		printf("Pipe Left: %p\n", pipe->left);
		if (pipe->left)
		{
			printf("Type_Left: %i\n", pipe->left->type);
			printf("\n\n");
			print_tree(&(pipe->left));
		}
		printf("Pipe Right: %p\n", pipe->right);
		if (pipe->right)
		{
			printf("Type_Right: %i\n", pipe->right->type);
			printf("\n\n");
			print_tree(&(pipe->right));
		}
		return ;
	}
	else if ( *tree && (*tree)->type == NODE_REDIRECT)
	{
		redir = (t_redir *)(*tree);
		printf("Redir Type: %i\n", redir->type);
		printf("Redir Arg: %s\n",redir->file);
		printf("Redir End Arg: %s\n",redir->file);
		printf("\n\n");
		if (redir->cmd)
			print_tree(&(redir->cmd));
		return ;
	}
	else if ( *tree && (*tree)->type == NODE_EXEC)
	{
		exec = (t_exec *)(*tree);
		printf("Exec Type: %i\n", exec->type);
		printf("Exec Command: %s\n", exec->cmd);
		int i = -1;
		while(exec->argv[++i])
		{
			printf("Exec Arrg: %s\n", exec->argv[i]);
			printf("Exec End Arg: %s\n", exec->eargv[i]);
		}
		printf("\n\n");
		return ;
	}
}

/// @brief Creates the token depending on the type and adds it to the AST
/// @param instr The pointer to the instruction
/// @param tree The tree structure to be filled
/// @return The length of the instruction
t_cmd	*pipe_token(t_cmd **tree)
{
	t_pipe	*node;
	// int		i;

	// i = 0;
	node = ft_calloc(1, sizeof(t_pipe));
	if (!node)
		ft_error("Allocation error", GENERAL_ERROR);
	node->type = NODE_PIPE;
	node->left = NULL;
	node->right = NULL;
	arrange_pipe_tree(tree, node);
	print_tree(tree);
	return ((t_cmd *)node);
}

/// @brief Creates, initializes and returns a redirect node for the AST
/// @param root Pointer to the command position
/// @return The pointer to the node
int		redirect_token(char *instr, t_cmd **tree)
{
	t_redir	*node;
	t_word	word;
	int		i;

	node = ft_calloc(1, sizeof(t_redir));
	if (!node)
		ft_error("Allocation error", GENERAL_ERROR);
	i = end_expression(instr, &word);
	node->type = NODE_REDIRECT;
	node->cmd = NULL;
	node->file = word.start;
	node->efile = word.end;
	node->mode = redirect_type(instr);
	node->fd = 0;
	print_tree(tree);
	arrange_redir_tree(tree, node);
	return (i);
}

/// @brief Creates, initializes and returns a command node for the AST
/// @param root Pointer to the command position
/// @return The pointer to the node
int		command_token(t_shell *sh, t_array *array, t_cmd **tree)
{
	t_exec	*node;
	int		i;

	i = 0;
	node = ft_calloc(1, sizeof(t_exec));
	if (!node)
		ft_error("Allocation error", GENERAL_ERROR);
	node->type = NODE_EXEC;
	node->cmd = array->start[0];
	node->argv = array->start;
	node->eargv = array->end;
	node->sh = sh;
	print_tree(tree);
	arrange_command_tree(tree, node);
	return (i);
}
