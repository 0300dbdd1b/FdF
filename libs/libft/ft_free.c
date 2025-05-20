/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaddino <noaddino@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 23:31:34 by noaddino          #+#    #+#             */
/*   Updated: 2025/04/17 23:32:28 by noaddino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(void *ptr)
{
	t_memheader	*header;

	if (!ptr)
		return ;
	header = ((t_memheader *)ptr) - 1;
	free(header);
}
