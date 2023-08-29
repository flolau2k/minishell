/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:10:26 by flauer            #+#    #+#             */
/*   Updated: 2023/08/25 19:07:13 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
// #include <criterion/criterion.h>
// #include <criterion/new/assert.h>
// #include <criterion/redirect.h>

// void init_cr(void)
// {
// 	cr_redirect_stdout();
// }
// TestSuite(do_exec_test, .init = init_cr);

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