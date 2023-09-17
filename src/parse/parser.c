/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:54:59 by flauer            #+#    #+#             */
/*   Updated: 2023/09/17 01:35:44 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_copystr(char *start, char *end)
{
	int		i;
	char	*tmp;

	i = 0;
	while (start + i <= end)
		i++;
	tmp = ft_substr(start, 0, i);
	return (tmp);
}

/// @brief The function will copy the arguments for the command arguments for the expander
/// @param array 
void	parse(char *argv, char *eargv)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_copystr(argv, eargv);
	free(argv);
	argv = tmp;
}

// /// @brief Parsing the AST received from the lexer
// /// @param tree root of the AST
// void	do_parsing(t_cmd *tree)
// {
// 	t_pipe	*pipe;
// 	t_redir	*redir;
// 	t_exec	*exec;
// 	int		i;

// 	i = 0;
// 	if ( tree && (tree)->type == NODE_PIPE)
// 	{
// 		pipe = (t_pipe *)(tree);
// 		if (pipe->left)
// 			do_parsing(pipe->left);
// 		if (pipe->right)
// 			do_parsing(pipe->right);
// 		return ;
// 	}
// 	else if ( tree && (tree)->type == NODE_REDIRECT)
// 	{
// 		redir = (t_redir *)(tree);
// 		// i = -1;
// 		// while(redir->argv[++i])
// 		// 	parse(redir->argv[i], redir->eargv[i], redir->flag[i]);
// 		if (redir->cmd)
// 			do_parsing(redir->cmd);
// 		return ;
// 	}
// 	else if ( tree && (tree)->type == NODE_EXEC)
// 	{
// 		exec = (t_exec *)(tree);

// 		i = -1;
// 		while(exec->argv[++i])
// 			parse(exec->argv[i], exec->eargv[i]);
// 		return ;
// 	}
// }
