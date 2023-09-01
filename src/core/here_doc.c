/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:23:26 by flauer            #+#    #+#             */
/*   Updated: 2023/09/01 12:34:35 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	hd_child(t_cmd *redir) //TODO check length!
{
	char	*line;
	char	*nlim;
	t_redir	*red;

	red = (t_redir *)redir;
	nlim = ft_strjoin((char *)red->file, "\n");
	write(red->ttyout, HERE_DOC_PROMPT, ft_strlen(HERE_DOC_PROMPT) - 1);
	line = get_next_line(red->ttyin);
	while (ft_strncmp(line, nlim, ft_strlen(nlim)))
	{
		printf("%s", line);
		free(line);
		write(red->ttyout, HERE_DOC_PROMPT, ft_strlen(HERE_DOC_PROMPT) - 1);
		line = get_next_line(red->ttyin);
	}
	free(line);
	free(nlim);
	exit(0);
}

void	here_doc(t_redir *redir)
{
	pid_t	pid;

	pid = create_pipe(&hd_child, (t_cmd *)redir);
	waitpid(pid, NULL, 0);
}
