/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaudin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 22:29:25 by ggaudin-          #+#    #+#             */
/*   Updated: 2018/03/06 16:02:22 by jlajovec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

int			count_result(int count, int f_id)
{
	if ((f_id == CYLINDER || f_id == CONE) && count != 11)
		return (1);
	else if (f_id == HYPERBOL && count != 10)
		return (1);
	else if (f_id == PLANE && count != 9)
		return (1);
	else if (f_id == SPHERE && count != 7)
		return (1);
	else if (f_id == LIGHT && count != 9)
		return (1);
	else if (f_id == 6 && count != 6)
		return (1);
	return (0);
}

int			final_check_forms(t_env *e, t_sce *s, int l, int f_id)
{
	int		x;
	int		count;

	x = 0;
	count = 0;
	if (!(s->tmp = (char*)malloc(sizeof(char) * (int)ft_strlen(e->map[l]) + 1)))
		ft_exit("Error malloc tmp");
	while (e->map[l][x] != '[')
		x++;
	while (e->map[l][++x] != ']' && e->map[l][x])
		while ((e->map[l][x] == ',' || e->map[l][x] == ' ' ||
			e->map[l][x] == '-' || ft_isdigit(e->map[l][x]) == 1) &&
				e->map[l][x])
		{
			if (ft_isdigit(e->map[l][x]) == 1 && (e->map[l][x + 1] == ',' ||
				e->map[l][x + 1] == ']') && e->map[l][x] != ' ' &&
					e->map[l][x] != '-')
			{
				count++;
				break ;
			}
			x++;
		}
	free(s->tmp);
	return (count_result(count, f_id));
}

int			check_name(t_env *e, t_sce *s, int param_nb)
{
	int		i;
	int		j;
	int		len;

	i = 1;
	j = 0;
	if (ft_strstr(e->map[param_nb], "scene_name=[") != NULL)
	{
		len = (int)ft_strlen(e->map[param_nb]);
		if ((s->name = (char*)malloc(sizeof(char) * (len + 1))) == 0)
			ft_exit("Scene malloc failed.");
		while (e->map[param_nb][i++])
			if (e->map[param_nb][i - 1] == '[')
				while (e->map[param_nb][i] != ']')
				{
					if (e->map[param_nb][i] == ' ')
						ft_exit("No space(s) allowed in scene name. Exiting.");
					s->name[j++] = e->map[param_nb][i++];
				}
		s->name[j] = '\0';
		return (0);
	}
	return (1);
}

int			check_form3(t_env *e, t_sce *s, int i)
{
	if (ft_strnstr(e->map[i], "cylinder=[", 10) != NULL)
	{
		set_form(s, i - P_SCENE, CYLINDER);
		s->forms[i - P_SCENE]->pos = vec();
		s->forms[i - P_SCENE]->col = col();
		return (check_cylinder(e, s, i, 0));
	}
	else if (ft_strnstr(e->map[i], "hyperboloid=[", 13) != NULL)
	{
		set_form(s, i - P_SCENE, HYPERBOL);
		s->forms[i - P_SCENE]->pos = vec();
		s->forms[i - P_SCENE]->col = col();
		return (check_hyperbol(e, s, i, 0));
	}
	return (1);
}

int			check_form2(t_env *e, t_sce *s, int i)
{
	if (ft_strnstr(e->map[i], "sphere=[", 8) != NULL)
	{
		set_form(s, i - P_SCENE, SPHERE);
		s->forms[i - P_SCENE]->pos = vec();
		s->forms[i - P_SCENE]->col = col();
		return (check_sphere(e, s, i, 0));
	}
	else if (ft_strnstr(e->map[i], "cone=[", 6) != NULL)
	{
		set_form(s, i - P_SCENE, CONE);
		s->forms[i - P_SCENE]->pos = vec();
		s->forms[i - P_SCENE]->col = col();
		return (check_cone(e, s, i, 0));
	}
	else
		return (check_form3(e, s, i));
	return (1);
}
