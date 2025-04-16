/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaddino <noaddino@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:59:40 by noaddino          #+#    #+#             */
/*   Updated: 2025/04/10 16:34:02 by noaddino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

static size_t	ft_word_count(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static char	*ft_strdup_range(const char *s, size_t start, size_t end)
{
	char	*str;
	size_t	i;

	str = malloc(end - start + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

static void	ft_free_split(char **split, size_t i)
{
	while (i--)
		free(split[i]);
	free(split);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	i;
	size_t	start;
	size_t	end;

	if (!s)
		return (NULL);
	res = malloc((ft_word_count(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	end = 0;
	while (i < ft_word_count(s, c))
	{
		while (s[end] == c)
			end++;
		start = end;
		while (s[end] && s[end] != c)
			end++;
		res[i++] = ft_strdup_range(s, start, end);
		if (!res[i - 1])
			return (ft_free_split(res, i - 1), NULL);
	}
	res[i] = NULL;
	return (res);
}
