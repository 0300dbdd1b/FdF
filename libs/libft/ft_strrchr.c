/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaddino <noaddino@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:00:18 by noaddino          #+#    #+#             */
/*   Updated: 2025/04/10 16:31:50 by noaddino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *str, int c)
{
	size_t	i;
	char	*last_occurrence;

	i = 0;
	last_occurrence = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			last_occurrence = (char *)(str + i);
		i++;
	}
	if (c == '\0')
		return ((char *)(str + i));
	return (last_occurrence);
}
