/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:04:24 by flauer            #+#    #+#             */
/*   Updated: 2023/08/31 15:35:37 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	exec.cmd = "env";
	exec.argv = (char *[]){"env", NULL};
	exec.eargv = (char *[]){NULL};
	exec.sh = &sh;
	t_exec	exe2;
	exec.type = NODE_EXEC;
	exec.pid = -1;
	exec.cmd = "export";
	exec.argv = (char *[]){"export", "TEST=HALLO", NULL};
	exec.eargv = (char *[]){NULL};
	exec.sh = &sh;
	t_exec	exe3;
	exec.type = NODE_EXEC;
	exec.pid = -1;
	exec.cmd = "env";
	exec.argv = (char *[]){"env", NULL};
	exec.eargv = (char *[]){NULL};
	exec.sh = &sh;
	// t_exec	exe2;
	// exe2.type = NODE_EXEC;
	// exe2.pid = -1;
	// exe2.cmd = "wc";
	// exe2.argv = (char *[]){"wc", "-l", NULL};
	// exe2.eargv = (char *[]){NULL};
	// exe2.sh = &sh;
	// t_redir	redir;
	// redir.type = NODE_REDIRECT;
	// redir.pid = -1;
	// redir.cmd = (t_cmd *)&exe2;
	// redir.file = "out.txt";
	// redir.efile = NULL;
	// redir.mode = O_WRONLY | O_CREAT | O_TRUNC;
	// redir.ttyin = sh.ttyin;
	// redir.ttyout = sh.ttyout;
	// redir.fd = 0;
	// t_pipe	pipe;
	// pipe.type = NODE_PIPE;
	// pipe.pid = -1;
	// pipe.left = (t_cmd *)&exec;
	// pipe.right = (t_cmd *)&redir;
	// root = (t_cmd *)&pipe;
	// t_exec	exe3;
	// exe3.type = NODE_EXEC;
	// exe3.pid = -1;
	// exe3.cmd = "cat";
	// exe3.argv = (char *[]){"cat", NULL};
	// exe3.eargv = (char *[]){NULL};
	// exe3.sh = &sh;
	// t_redir	red2;
	// red2.type = NODE_REDIRECT;
	// red2.pid = -1;
	// red2.cmd = (t_cmd *)&exe3;
	// red2.file = "LIM";
	// red2.efile = NULL;
	// red2.mode = O_HEREDOC;
	// red2.ttyin = sh.ttyin;
	// red2.ttyout = sh.ttyout;
	// red2.fd = 0;
	// t_pipe	pip2;
	// pip2.type = NODE_PIPE;
	// pip2.pid = -1;
	// pip2.left = (t_cmd *)&red2;
	// pip2.right = (t_cmd *)&pipe;
	root = (t_cmd *)&exec;
	execute(root);
	execute((t_cmd *)&exe2);
	execute((t_cmd *)&exe3);
	// printf("exit code: %i\n", sh.ret);
	return (0);
}

// << LIM cat | grep Petru | wc -l >out.txt