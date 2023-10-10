/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:04:24 by flauer            #+#    #+#             */
/*   Updated: 2023/10/10 12:49:12 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_sig = 0;

void	print_token_list(t_list *token_str)
{
	t_list	*temp;
	t_token	*content;

	temp = token_str;
	content = (t_token *) temp->content;
	while (temp)
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

static void	reset_shell(t_list *token_str, t_cmd *root, t_shell *sh, bool flag)
{
	int		i;
	char	*fname[2];

	i = 0;
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
	}
	while (i < sh->n_hd)
	{
		fname[0] = ft_itoa(i);
		fname[1] = ft_strjoin(".hd_tmp", fname[0]);
		unlink(fname[1]);
		free(fname[0]);
		free(fname[1]);
		i++;
	}
	sh->n_hd = 0;
}

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
		rec_execute(root);
		reset_shell(token_str, NULL, sh, false);
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

	signal(SIGINT, &signal_handler);
	init(&sh, argc, argv, env);
	main_loop(&sh);
}
