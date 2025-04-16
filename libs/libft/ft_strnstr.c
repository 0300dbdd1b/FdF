/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaddino <noaddino@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:00:16 by noaddino          #+#    #+#             */
/*   Updated: 2025/04/10 16:54:48 by noaddino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *h, const char *n, size_t l)
{
	size_t	i;
	size_t	j;

	if (!h && l == 0)
		return (NULL);
	if (!n[0])
		return ((char *)h);
	i = 0;
	while (h[i] && i < l)
	{
		j = 0;
		while (h[i + j] && n[j] && i + j < l && h[i + j] == n[j])
			j++;
		if (!n[j])
			return ((char *)(h + i));
		i++;
	}
	return (NULL);
}
