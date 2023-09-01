/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:28:41 by flauer            #+#    #+#             */
/*   Updated: 2023/09/01 16:26:13 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_cmd_path(char *name, char **env)
{
	char	**paths;
	char	*path;
	char	*cmd;
	int		i;

	i = 0;
	cmd = NULL;
	paths = get_env_s(env, "PATH");
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
	free_arr(paths);
	return (cmd);
}

/// @brief get the values of a given key from the environment
/// @param env the environment
/// @param key desired key
/// @return string array with the values, NULL if the key is not in environment.
/// return may be free'd if not NULL.
char	**get_env_s(char **env, char *key)
{
	char	**ret;
	char	*val;

	val = get_env(env, key);
	if (!val)
		return (NULL);
	ret = ft_split(val, ':');
	free(val);
	return (ret);
}

char	*get_cmd(char *name, char **env)
{
	if (!name)
		return (NULL);
	else if (ft_strnstr(name, "/", ft_strlen(name)))
		return (ft_strdup(name));
	else
		return (get_cmd_path(name, env));
}
