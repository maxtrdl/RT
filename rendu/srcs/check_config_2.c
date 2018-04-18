/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaudin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 22:32:24 by ggaudin-          #+#    #+#             */
/*   Updated: 2018/02/25 14:58:48 by agaspard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

static int	check_shine_2(t_sce *s)
{
	if (ft_strcmp("yes", s->tmp) == 0)
		s->shine = 0;
	else if (ft_strcmp("no", s->tmp) == 0)
		s->shine = 1;
	else
		ft_exit("shine option must be set as 'yes' or 'no'");
	free(s->tmp);
	return (0);
}

int			check_shine(t_env *e, t_sce *s, int p)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (ft_strstr(e->map[p], "shine=[") != NULL)
	{
		if ((s->tmp = (char *)ft_memalloc(sizeof(char) * (4))) == 0)
			ft_exit("error malloc");
		while (e->map[p][i])
		{
			if (e->map[p][i] == '[')
			{
				i++;
				while (e->map[p][i] != ']')
					s->tmp[j++] = e->map[p][i++];
			}
			i++;
		}
		return (check_shine_2(s));
	}
	return (1);
}

static int	check_shadow_2(t_sce *s)
{
	if (ft_strcmp("yes", s->tmp) == 0)
		s->shadow = 1;
	else if (ft_strcmp("no", s->tmp) == 0)
		s->shadow = 0;
	else
		ft_exit("shadow option must be set as 'yes' or 'no'");
	free(s->tmp);
	return (0);
}

int			check_shadow(t_env *e, t_sce *s, int p, int x)
{
	int j;

	j = 0;
	if (ft_strstr(e->map[p], "shadow=[") != NULL)
	{
		if ((s->tmp = (char*)ft_memalloc(sizeof(char) * 4)) == 0)
			ft_exit("error malloc");
		while (e->map[p][x])
		{
			if (e->map[p][x] == '[')
			{
				x++;
				while (e->map[p][x] != ']')
					s->tmp[j++] = e->map[p][x++];
			}
			x++;
		}
		return (check_shadow_2(s));
	}
	return (1);
}
