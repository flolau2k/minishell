/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:57:56 by flauer            #+#    #+#             */
/*   Updated: 2023/08/29 16:18:44 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	do_lexing("< <here cat | fdks asdf asdfadsfjljadsf\"adsfadsf\" 'adsfadgsa\"asdf\"' asd|ads grep > >out");
	return (0);
}
// void	f_echo(t_exec *cmd)
// {
// 	int		i;
// 	bool	nl;

// 	nl = true;
// 	i = 1;
// 	if (cmd->argv[1] && ft_strncmp(cmd->argv[1], "-n", 3) == 0)
// 	{
// 		nl = false;
// 		i = 2;
// 	}
// 	while (cmd->argv[i])
// 	{
// 		printf("%s", cmd->argv[i]);
// 		i++;
// 	}
// 	if (nl)
// 		printf("\n");
// 	return (free_exec(cmd));
// }

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	(void) env;
	t_exec	exec;

	exec = (t_exec){
		.type = NODE_EXEC,
		.cmd = "cd",
		.argv = NULL,
		.eargv = NULL,
		.sh = NULL
		};
	
	do_exec(&exec);
	// cr_assert_stdout_eq("test");
	return (0);
}
