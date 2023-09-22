/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:04:59 by pcazac            #+#    #+#             */
/*   Updated: 2023/09/22 18:13:47 by pcazac           ###   ########.fr       */
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

int	is_variable(t_shell *sh, char *arg, char **new)
{
	int		i;
	char	*key;
	char	*temp;

	key = NULL;
	temp = NULL;
	i = 0;
	while (arg[i] && (ft_isalnum(arg[i]) || arg[i] == '_'))
				i++;
	key = ft_substr(arg, 0, i);
	if (!key)
		ft_error("malloc", strerror(errno), GENERAL_ERROR);
	temp = get_env(sh->env, key);
	if (!temp)
	{	
		free(key);
		*new = ft_strdup("");
		return (i);
	}
	*new = ft_strdup(temp);
	free(key);
	return (i);
}

int	not_variable(char *arg, char **val)
{
	int		i;

	i = 0;
	while (arg[i] && arg[i] != '$' )
		i++;
	*val = ft_substr(arg, 0, i);
	if (i > 0)
		i--;
	if (!*val)
		ft_error("malloc", strerror(errno), GENERAL_ERROR);
	return (i);
}
