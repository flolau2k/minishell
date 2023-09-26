/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:36:37 by flauer            #+#    #+#             */
/*   Updated: 2023/09/26 14:50:39 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/// @brief appends string src to the end of dst. it will append at most 
/// dstsize - strlen(dst) - 1 characters, NUL-terminating the result, unless
/// dstsize is 0 or the original dst string was longer than dstsize.
/// @param dst destination string
/// @param src source string
/// @param dstsize size of the dst buffer
/// @return the length of the string that was tried to create. If the return
/// value is >= dstsize, the output string has been truncated. It is the 
/// callers responsibility to handle this!
size_t	ft_strlcat_s(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	dstlen;

	dstlen = ft_strlen_s(dst);
	if (dstlen > dstsize)
		return (dstsize + ft_strlen_s(src));
	if (!src)
		return (0);
	i = 0;
	while (src[i] && (i + dstlen + 1) < dstsize)
	{
		dst[i + dstlen] = src[i];
		i++;
	}
	dst[i + dstlen] = 0;
	return (dstlen + ft_strlen_s(src));
}

/// @brief get the total length of string s
/// @param s string s
/// @return total length of s
size_t	ft_strlen_s(const char *s)
{
	size_t	ret;

	ret = 0;
	if (s == NULL)
		return (0);
	while (s[ret])
		ret++;
	return (ret);
}

/// @brief allocates a new buffer and returns a new string, which is
/// the result of the concatenation 
/// @param s1 first string
/// @param s2 second string
/// @return new string with the concatenated strings s1 and s2
char	*ft_strjoin_s(char const *s1, char const *s2)
{
	char	*ret;

	ret = ft_calloc(ft_strlen_s(s1) + ft_strlen_s(s2) + 1, sizeof(char));
	if (!ret)
		return (NULL);
	ft_strlcat_s(ret, s1, ft_strlen_s(s1) + 1);
	ft_strlcat_s(ret + ft_strlen_s(s1), s2, ft_strlen_s(s2) + 1);
	return (ret);
}
