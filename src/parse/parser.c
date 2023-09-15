/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:54:59 by flauer            #+#    #+#             */
/*   Updated: 2023/09/15 12:04:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/// @brief Parsing the AST received from the lexer
/// @param tree root of the AST
void	do_parsing(t_cmd *tree)
{
	t_pipe	*pipe;
	t_redir	*redir;
	t_exec	*exec;


	if ( tree && (tree)->type == NODE_PIPE)
	{
		pipe = (t_pipe *)(tree);
		if (pipe->left)
			do_parsing(pipe->left);
		if (pipe->right)
			do_parsing(pipe->right);
		return ;
	}
	else if ( tree && (tree)->type == NODE_REDIRECT)
	{
		redir = (t_redir *)(tree);
		redir->eargv[0] = '\0';
		if (redir->cmd)
			do_parsing(redir->cmd);
		return ;
	}
	else if ( tree && (tree)->type == NODE_EXEC)
	{
		exec = (t_exec *)(tree);

		int i = -1;
		while(exec->eargv[++i])
			exec->eargv[i][0] = '\0';
		return ;
	}
}
