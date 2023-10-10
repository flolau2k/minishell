/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:23:26 by flauer            #+#    #+#             */
/*   Updated: 2023/10/10 12:50:28 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*hd_parse(char *lim, t_shell *sh)
{
	char		*line[2];
	char		*nlim;
	char		*fname;
	int			fd;

	nlim = ft_itoa(sh->n_hd);
	fname = ft_strjoin(".hd_tmp", nlim);
	(sh->n_hd)++;
	free(nlim);
	fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// nlim = ft_strjoin(lim, "\n");
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
