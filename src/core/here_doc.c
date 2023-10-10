/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:23:26 by flauer            #+#    #+#             */
/*   Updated: 2023/10/10 13:43:20 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*find_fname(void)
{
	int		n;
	char	*nlim;
	char	*fname;

	n = 0;
	while (true)
	{
		nlim = ft_itoa(n);
		fname = ft_strjoin(".hd_tmp", nlim);
		free(nlim);
		if (access(fname, F_OK))
			break ;
		free(fname);
		n++;
	}
	return (fname);
}

char	*hd_parse(char *lim, t_shell *sh)
{
	char	*line[2];
	char	*fname;
	int		fd;

	fname = find_fname();
	fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_lstadd_back(&(sh->tmp_files), ft_lstnew(ft_strdup(fname)));
	line[0] = readline(HERE_DOC_PROMPT);
	while (line[0] && ft_strncmp(line[0], lim, ft_strlen(line[0])))
	{
		line[1] = expand(line[0], sh);
		ft_fprintf(fd, "%s\n", line[1]);
		free(line[0]);
		free(line[1]);
		line[0] = readline(HERE_DOC_PROMPT);
	}
	free(line[0]);
	close(fd);
	return (fname);
}
