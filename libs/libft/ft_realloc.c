/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaddino <noaddino@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 23:30:14 by noaddino          #+#    #+#             */
/*   Updated: 2025/04/17 23:31:22 by noaddino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t new_size)
{
	t_memheader	*old_header;
	void		*new_ptr;
	size_t		copy_size;

	if (!ptr)
		return (ft_malloc(new_size));
	if (new_size == 0)
	{
		ft_free(ptr);
		return (NULL);
	}
	old_header = ((t_memheader *)ptr) - 1;
	new_ptr = ft_malloc(new_size);
	if (!new_ptr)
		return (NULL);
	copy_size = old_header->size;
	if (copy_size > new_size)
		copy_size = new_size;
	ft_memcpy(new_ptr, ptr, copy_size);
	ft_free(ptr);
	return (new_ptr);
}
