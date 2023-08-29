/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:04:24 by flauer            #+#    #+#             */
/*   Updated: 2023/08/29 17:51:21 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	main_loop(t_shell *sh)
// {
// 	t_cmd	*root;

// 	if (sh->line)
// 	{
// 		root = do_lexing(sh);
// 		execute(root);
// 	}
// 	while (true)
// 	{
// 		sh->line = readline(MINISHELL_PROMPT);
// 		root = do_lexing(sh);
// 		execute(root);
// 		free(sh->line);
// 		// free root tree;
// 	}
// }

// int	main(int argc, char **argv, char **env)
// {
// 	t_shell	sh;

// 	init(&sh, argc, argv, env);
// 	// signals()
// 	main_loop()

// }

int	main(int argc, char **argv, char **env)
{
	t_shell	sh;

	init(&sh, argc, argv, env);
	t_cmd	*root;
	t_exec	exec;
	exec.type = NODE_EXEC;
	exec.pid = -1;
	exec.cmd = "ls";
	exec.argv = (char *[]){"ls", "-l", NULL};
	exec.eargv = (char *[]){NULL};
	exec.sh = &sh;
	root = (t_cmd *)&exec;
	execute(root);
	return (0);
}
