/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:23:26 by flauer            #+#    #+#             */
/*   Updated: 2023/10/12 16:13:47 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/// @brief free a string array and it's contents.
/// @param arr array
void	free_arr(char **arr)
{
	int		i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/// @brief get lenth of string array
/// @param arr array
/// @return length
int	array_len(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

void	wait_exit(void)
{
	pid_t	pid;

	pid = waitpid(0, NULL, 0);
	while (pid != -1)
		pid = waitpid(0, NULL, 0);
}

bool	is_valid_identfier(char *new, bool flag)
{
	int	i;

	i = 0;
	if (new[i] && ft_isdigit(new[i]))
		return (false);
	while (new[i])
	{
		if (ft_isalnum(new[i]) || new[i] == '_')
			i++;
		else if (flag && new[i] == '=')
			break ;
		else
			return (false);
	}
	if (i == 0)
		return (false);
	return (true);
}

void	open_failure(t_redir *redir)
{
	ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n",
		redir->file, strerror(errno));
	if (redir->pid != -1)
	{
		free_tree_shell((t_cmd *)redir);
		exit(GENERAL_ERROR);
	}
	redir->sh->ret = GENERAL_ERROR;
	free_redir(redir);
}
