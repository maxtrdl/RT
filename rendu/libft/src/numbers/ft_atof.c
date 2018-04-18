/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrudel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 15:49:17 by mtrudel           #+#    #+#             */
/*   Updated: 2018/03/02 14:49:10 by jlajovec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_atoi_pos(const char *str)
{
	int i;
	int res;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res);
}

double		ft_atof(char *str)
{
	int		neg;
	int		i;
	int		j;
	double	tmp;
	double	res;

	i = 0;
	neg = 0;
	tmp = 0.00;
	j = 10;
	neg = (str[0] == '-') ? 1 : 0;
	res = ft_atoi_pos(str);
	while (str[i] != '.' && str[i])
		i++;
	if (str[i] == '.' && str[i + 1] >= '0' && str[i] <= '9')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = str[i] - '0';
		res += tmp / j;
		j *= 10;
		i++;
	}
	return ((neg == 1) ? -res : res);
}
