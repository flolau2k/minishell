/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:04:24 by flauer            #+#    #+#             */
/*   Updated: 2023/09/22 17:35:43 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_token_list(t_list *token_str)
{
	t_list	*temp;
	t_token	*content;

	temp = token_str;
	content = (t_token *) temp->content;
	while(temp)
	{
		ft_printf("----Token----\n");
		content = temp->content;
		ft_printf("Type:%i\n", content->type);
		ft_printf("Content:");
		write(1, content->start, content->length);
		write(1, "\n", 1);
		ft_printf("Length:%i\n", content->length);
		ft_printf("Flag:%i\n", content->flag);
		temp = temp->next;
	}
	
}

int	g_sig = 0;

void	reset_shell(t_shell *sh)
{
	dup2(sh->ttyin, STDIN_FILENO);
	dup2(sh->ttyout, STDOUT_FILENO);
	printf("%s", NO_COLOR);
}

void	main_loop(t_shell *sh)
{
	t_cmd	*root;	
	t_list	*token_str;
	
	while (true)
	{
		root = NULL;
		// if (isatty(fileno(stdin)))
		// 	sh->line = readline(MINISHELL_PROMPT);
		// else
		// {
		// 	char *line;
		// 	line = get_next_line(fileno(stdin));
		// 	sh->line = line;
		// 	if (line)
		// 		sh->line = ft_strtrim(line, "\n");
		// 	free(line);
		// }
		sh->line = readline(MINISHELL_PROMPT);
		if (g_sig)
		{
			sh->ret = 128 + g_sig;
			g_sig = 0;
		}
		if (!sh->line)
			f_exit2(sh, "exit", EXIT_SUCCESS);
		if (ft_strlen(sh->line) == 0)
			continue ;
		add_history(sh->line);
		if (!quote_check(sh->line))
		{
			free(sh->line);
			continue ;
		}
		token_str = do_lexing(sh->line);
		// print_token_list(token_str);
		parser(token_str, &root, sh);
		print_tree(&root);
		free(sh->line);
		sh->line = NULL;
		print_tree(&root);
		rec_execute(root);
		reset_shell(sh);
	}
}

void	leaks_check(void)
{
	system("leaks minishell");
}

/// @brief main function of minishell
/// @param argc input arg count
/// @param argv arg values
/// @param env env values
/// @return exit code
int	main(int argc, char **argv, char **env)
{
	t_shell	sh;

	// atexit(leaks_check);
	signal(SIGINT, &signal_handler);
	init(&sh, argc, argv, env);
	main_loop(&sh);
}
