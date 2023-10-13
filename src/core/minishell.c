/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:04:24 by flauer            #+#    #+#             */
/*   Updated: 2023/10/13 08:49:46 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_sig = 0;

void	clear_tmp_file(void *arg)
{
	unlink((char *)arg);
}

static void	reset_shell(t_list *token_str, t_cmd *root, t_shell *sh, bool flag)
{
	if (token_str)
		ft_lstclear(&token_str, &free_token);
	if (root)
		free_tree(root);
	free(sh->line);
	sh->line = NULL;
	if (flag)
	{
		dup2(sh->ttyin, STDIN_FILENO);
		dup2(sh->ttyout, STDOUT_FILENO);
		ft_lstiter(sh->tmp_files, &clear_tmp_file);
		ft_lstclear(&(sh->tmp_files), &free);
	}
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	main_loop(t_shell *sh)
{
	t_cmd	*root;
	t_list	*token_str;

	while (true)
	{
		reset_shell(NULL, NULL, sh, true);
		root = NULL;
		sh->line = readline(MINISHELL_PROMPT);
		apply_signal(sh);
		if (!sh->line)
			f_exit2(sh, NULL, sh->ret);
		if (ft_strlen(sh->line) == 0)
			continue ;
		add_history(sh->line);
		if (!quote_check(sh->line))
			continue ;
		token_str = do_lexing(sh->line);
		if (!parser(token_str, &root, sh))
		{
			reset_shell(token_str, root, sh, false);
			continue ;
		}
		reset_shell(token_str, NULL, sh, false);
		rec_execute(root);
	}
}

/// @brief main function of minishell
/// @param argc input arg count
/// @param argv arg values
/// @param env env values
/// @return exit code
int	main(int argc, char **argv, char **env)
{
	t_shell	sh;

	init(&sh, argc, argv, env);
	main_loop(&sh);
}
