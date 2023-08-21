/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:11:16 by flauer            #+#    #+#             */
/*   Updated: 2023/08/21 15:20:59 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief get the values of a given key from the environment
/// @param env the environment
/// @param key desired key
/// @return string array with the values, NULL if the key is not in environment
char	**get_env(char *env[], char *key)
{
	int		i;
	char	*trim;
	char	**ret;

	i = 0;
	trim = NULL;
	ret = NULL;
	if (ft_strlen(key) == 0)
		return (NULL);
	while (env[i])
	{
		if (ft_strnstr(env[i], key, ft_strlen(key)))
		{
			trim = ft_substr(env[i], ft_strlen(key) + 1, \
				ft_strlen(env[i]) - ft_strlen(key) - 1);
			ret = ft_split(trim, ':');
			free(trim);
			return (ret);
		}
		++i;
	}
	return (NULL);
}

char	*get_cmd_path(char *name, char *env[])
{
	char	**paths;
	char	*path;
	char	*cmd;
	int		i;

	i = 0;
	cmd = NULL;
	paths = get_env(env, "PATH");
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		cmd = ft_strjoin(path, name);
		free(path);
		if (!access(cmd, X_OK))
			break ;
		free(cmd);
		cmd = NULL;
		++i;
	}
	free_splits(paths);
	return (cmd);
}

char	*get_cmd(char *name, char *env[])
{
	if (!name)
		return (NULL);
	else if (ft_strnstr(name, "/", ft_strlen(name)))
		return (ft_strdup(name));
	else
		return (get_cmd_path(name, env));
}
