/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lazy-allocator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaddino <noaddino@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:09:56 by noaddino          #+#    #+#             */
/*   Updated: 2025/04/17 23:40:27 by noaddino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lazy_allocator	*create_lazy_allocator_segment(size_t size)
{
	t_lazy_allocator	*segment;

	segment = ft_malloc(sizeof(t_lazy_allocator));
	if (!segment)
		return (NULL);
	segment->ptr = ft_malloc(size);
	if (!segment->ptr)
	{
		ft_free(segment);
		return (NULL);
	}
	segment->next = NULL;
	return (segment);
}

void	*allocate_from_lazy_allocator(
	t_lazy_allocator **allocator,
	size_t size
)
{
	t_lazy_allocator	*segment;

	segment = create_lazy_allocator_segment(size);
	if (!segment)
		return (NULL);
	segment->next = *allocator;
	*allocator = segment;
	return (segment->ptr);
}

void	ft_free_from_lazy_allocator(
	t_lazy_allocator **allocator,
	void *ptr
)
{
	t_lazy_allocator	*current;
	t_lazy_allocator	*prev;

	current = *allocator;
	prev = NULL;
	while (current)
	{
		if (current->ptr == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				*allocator = current->next;
			ft_free(current->ptr);
			ft_free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	ft_free_lazy_allocator(t_lazy_allocator **allocator)
{
	t_lazy_allocator	*current;
	t_lazy_allocator	*next;

	current = *allocator;
	while (current)
	{
		next = current->next;
		ft_free(current->ptr);
		ft_free(current);
		current = next;
	}
	*allocator = NULL;
}

void	*realloc_from_lazy_allocator(
	t_lazy_allocator **allocator,
	void *ptr,
	size_t new_size
)
{
	t_lazy_allocator	*current;
	void				*new_ptr;

	if (!ptr)
		return (allocate_from_lazy_allocator(allocator, new_size));
	current = *allocator;
	while (current)
	{
		if (current->ptr == ptr)
		{
			new_ptr = ft_realloc(current->ptr, new_size);
			if (!new_ptr)
				return (NULL);
			current->ptr = new_ptr;
			return (new_ptr);
		}
		current = current->next;
	}
	return (NULL);
}
