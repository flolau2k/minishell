/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:28:41 by flauer            #+#    #+#             */
/*   Updated: 2023/09/05 17:42:02 by flauer           ###   ########.fr       */
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

char	**increment_env_var(char **env, char *key)
{
	int		itmp;
	char	*stmp[3];

	if (!get_env(env, key) || !ft_isdigit(get_env(env, key)[0]))
		return (env);
	itmp = (int) ft_atoi(get_env(env, key));
	stmp[0] = ft_itoa(itmp + 1);
	stmp[1] = ft_strjoin(key, "=");
	stmp[2] = ft_strjoin(stmp[1], stmp[0]);
	free(stmp[0]);
	free(stmp[1]);
	replace_in_env(env, stmp[2]);
	free(stmp[2]);
	return (env);
}

char	**set_default_env(char **env)
{
	char	*tmp[2];

	if (!get_env(env, "LS_COLORS"))
		env = set_env(env, "LS_COLORS=");
	if (!get_env(env, "LESSCLOSE"))
		env = set_env(env, "LESSCLOSE=/usr/bin/lesspipe %s %s");
	if (!get_env(env, "LESSOPEN"))
		env = set_env(env, "LESSOPEN=| /usr/bin/lesspipe %s");
	if (!get_env(env, "SHLVL"))
		env = set_env(env, "SHLVL=1");
	else
		env = increment_env_var(env, "SHLVL");
	if (!get_env(env, "PWD"))
	{
		tmp[0] = execute_command("/bin/pwd", (char *[]){"/bin/pwd", NULL});
		tmp[1] = ft_strjoin("PWD=", tmp[0]);
		free(tmp[0]);
		env = set_env(env, tmp[1]);
		free(tmp[1]);
	}
	return (env);
}
