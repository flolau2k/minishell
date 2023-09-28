/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:15:15 by flauer            #+#    #+#             */
/*   Updated: 2023/09/28 11:37:25 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_error(char *msg, char *errmsg, int excode)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (msg)
		printf("minishell: %s: %s\n", msg, errmsg);
	else
		printf("minishell: %s\n", errmsg);
	exit(excode);
}

void	ft_error2(char *msg, char *errmsg)
{
	int	tmp_stderr;
	
	tmp_stderr = dup(STDERR_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (msg)
		printf("minishell: %s: %s\n", msg, errmsg);
	else
		printf("minishell: %s\n", errmsg);
	dup2(STDOUT_FILENO, tmp_stderr);
}

void	ft_error3(char *msg, char *errmsg, int excode, void *tofree)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (msg)
		printf("minishell: %s: %s\n", msg, errmsg);
	else
		printf("minishell: %s\n", errmsg);
	free(tofree);
	exit(excode);
}