/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:04:59 by pcazac            #+#    #+#             */
/*   Updated: 2023/09/15 10:48:41 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_realloc(char *new, char *s, int count)
{
	char	*str;

	str = NULL;
	if (!new)
		return(s);
	if (s)
		count += ft_strlen(s);
	else
		return (new);
	str = ft_strjoin(new, s);
	free(new);
	new = NULL;
	free(s);
	s = NULL;
	return (str);
}

int	is_special_variable(t_shell *sh, char **new)
{
	*new = ft_itoa(sh->ret);
	if (!*new)
		*new = ft_strdup("");
	return (2);
}

int	is_variable(t_shell *sh, char *arg, char **new)
{
	int		i;
	int		count;
	char	*key;

	key = NULL;
	count = 0;
	i = 0;
	while (arg[++i] && (ft_isalnum(arg[i]) || arg[i] == '_'))
				count++;
	key = ft_substr(arg + i - count, 0, count);
	if (!key)
		ft_error("malloc", strerror(errno), GENERAL_ERROR);
	*new = ft_strdup(get_env(sh->env, key));
	free(key);
	return (i);
}

int	not_variable(char *arg, char **new)
{
	int		i;
	int		count;

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
	*new = ft_substr(arg + i - count, 0, count);
	if (!*new)
		ft_error("malloc", strerror(errno), GENERAL_ERROR);
	return (i);
}
