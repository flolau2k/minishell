/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:23:26 by flauer            #+#    #+#             */
/*   Updated: 2023/08/29 11:47:58 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	hd_child(char *lim)
{
	char	*line;
	char	*nlim;

	nlim = ft_strjoin((char *)lim, "\n");
	line = readline(HERE_DOC_PROMPT);
	while (ft_strncmp(line, nlim, ft_strlen(nlim)))
	{
		printf("%s", line);
		free(line);
		line = readline(HERE_DOC_PROMPT);
	}
	free(line);
	free(nlim);
	exit(0);
}

void	here_doc(char *lim)
{
	pid_t	pid;

	pid = create_pipe(&hd_child, lim);
	waitpid(pid, NULL, 0);
}
