/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:04:59 by pcazac            #+#    #+#             */
/*   Updated: 2023/09/06 11:48:49 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_special_variable(t_shell *sh, char **new)
{
	char	*smth;
	char	*smth2;

	smth = NULL;
	smth2 = NULL;
	smth = ft_itoa(sh->ret);
	if (!smth)
		smth = ft_strdup("");
	if (!(*new))
		*new = smth;
	else if (*new)
	{
		smth2 = ft_strjoin(*new, smth);
		free(smth);
		free(*new);
		*new = smth2;
	}
	return (2);
}

int	is_variable(t_shell *sh, char *arg, char **new)
{
	int		i;
	int		count;
	char	*key;
	char	*smth;
	char	*smth2;

	smth = NULL;
	smth2 = NULL;
	key = NULL;
	count = 0;
	i = 0;
	while (arg[++i] && (ft_isalnum(arg[i]) || arg[i] == '_'))
				count++;
	key = ft_substr(arg + i - count, 0, count);
	if (!key)
		ft_error("ALLOCATION ERROR", GENERAL_ERROR);
	smth = get_env(sh->env, key);
	free(key);
	if (!*new)
	{
		*new = smth;
	}
	else if (*new)
		smth2 = ft_strjoin(*new, smth);
	// free(smth);
	// free(*new);
	*new = smth2;
	return (i);
}

int	not_variable(char *arg, char **new)
{
	int		i;
	int		count;
	char	*key;
	char	*smth;
	char	*smth2;

	smth = NULL;
	smth2 = NULL;
	key = NULL;
	count = 0;
	i = 0;
	count = 0;
	while (arg[i])
	{
		if (arg[i] && arg[i] == '$')
			break;
		count++;
		i++;
	}
	smth = ft_substr(arg + i - count, 0, count);
	if (!smth)
		ft_error("ALLOCATION ERROR", GENERAL_ERROR);
	if (!*new)
	{
		*new = smth;
	}
	else
	{
		smth2 = ft_strjoin(*new, smth);
		// free(*new);
		// free(smth);
		*new = smth2;
	}
	return (i);
}
