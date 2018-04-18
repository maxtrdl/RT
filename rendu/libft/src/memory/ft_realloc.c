/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlajovec <jlajovec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 20:58:18 by jlajovec          #+#    #+#             */
/*   Updated: 2018/02/15 21:09:52 by jlajovec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void		*ft_realloc(void *ptr, size_t size)
{
	char	*newptr;

	if ((size == 0 || !size) && ptr)
	{
		if (!(newptr = (char *)malloc(1)))
			return (NULL);
		free(ptr);
		return (newptr);
	}
	if (ptr == NULL)
		if (!(newptr = (char *)malloc(sizeof(size))))
			return (NULL);
	if (!(newptr = (char *)malloc(size)))
		return (NULL);
	if (ptr)
	{
		ft_memcpy(newptr, ptr, size);
		free(ptr);
	}
	return (newptr);
}
