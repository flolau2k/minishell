/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:20:22 by pcazac            #+#    #+#             */
/*   Updated: 2023/09/07 15:55:39 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int	get_special_var(t_shell *sh, char **ret)
{
	int		count;
	int		i;
	char	*new;
	char	*s;

	count = 0;
	i = 0;
	s = NULL;
	new = NULL;
	i = is_special_variable(sh, &s);
	if (s)
		count += ft_strlen(s);
	if (!*ret)
		*ret = s;
	else
	{
		new = ft_strdup(*ret);
		free(*ret);
		*ret = ft_realloc(new, s, count);
	}
	return (i);
}

int	get_variable(t_shell *sh, char *arg, char **ret)
{
	int		count;
	int		i;
	char	*new;
	char	*s;
	
	count = 0;
	i = 0;
	s = NULL;
	new = NULL;
	i += is_variable(sh, arg + i, &s);
	if (s)
		count += ft_strlen(s);
	if (!*ret)
		*ret = s;
	else
	{
		new = ft_strdup(*ret);
		free(*ret);
		*ret = ft_realloc(new, s, count);
	}
	return (i);
}

int	get_non_variable(char *arg, char **ret)
{
	int		count;
	int		i;
	char	*new;
	char	*s;
	
	count = 0;
	i = 0;
	s = NULL;
	new = NULL;
	i += not_variable(arg + i, &s);
	if (s)
		count += ft_strlen(s);
	if (!*ret)
		*ret = s;
	else
	{
		new = ft_strdup(*ret);
		free(*ret);
		*ret = ft_realloc(new, s, count);
	}
	return (i);
}
