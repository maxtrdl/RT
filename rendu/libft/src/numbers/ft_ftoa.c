/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlajovec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 16:50:28 by jlajovec          #+#    #+#             */
/*   Updated: 2018/02/28 16:58:09 by jlajovec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static char	*ft_ftoa_is_neg(float n, char *part)
{
	char	*good;

	good = NULL;
	if (n < 0 && ft_atoi(part) == 0)
		good = ft_strjoin("-", part);
	else
		return (part);
	free(part);
	return (good);
}

char		*ft_ftoa(float n)
{
	int		tmp;
	float	new;
	char	*converted;
	char	*tmp1;
	char	*tmp2;

	tmp = (int)n;
	new = n - (float)tmp;
	while (new != (int)new)
		new *= 10;
	tmp1 = ft_itoa(tmp);
	tmp1 = ft_ftoa_is_neg(n, tmp1);
	tmp2 = ft_strjoin(tmp1, ".");
	free(tmp1);
	if (new < 0.0)
		new *= -1;
	tmp1 = ft_itoa((int)new);
	converted = ft_strjoin(tmp2, tmp1);
	free(tmp1);
	free(tmp2);
	return (converted);
}
