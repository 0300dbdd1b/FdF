/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaddino <noaddino@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 23:29:33 by noaddino          #+#    #+#             */
/*   Updated: 2025/04/17 23:30:59 by noaddino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_get_malloc_size(void *ptr)
{
	if (!ptr)
		return (0);
	return ((((t_memheader *)ptr) - 1)->size);
}

void	*ft_malloc(size_t size)
{
	t_memheader	*header;

	header = (t_memheader *)malloc(sizeof(t_memheader) + size);
	if (!header)
		return (NULL);
	header->size = size;
	return (header + 1);
}
