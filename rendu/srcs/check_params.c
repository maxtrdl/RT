/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaudin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 22:38:49 by ggaudin-          #+#    #+#             */
/*   Updated: 2018/03/06 16:01:59 by jlajovec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

void		set_form(t_sce *s, int i, int form_id)
{
	if ((s->forms[i] = (t_form*)malloc(sizeof(t_form))) == 0)
		ft_exit("struct forms malloc failed");
	s->forms[i]->form_id = form_id;
}

int			check_form(t_env *e, t_sce *s, int i)
{
	if (ft_strnstr(e->map[5], "ambient_light", 13) == NULL)
		ft_exit("Ambient light must be set to enlight your scene");
	if (ft_strstr(e->map[i], "light=[") != NULL)
	{
		set_form(s, i - P_SCENE, LIGHT);
		s->forms[i - P_SCENE]->pos = vec();
		s->forms[i - P_SCENE]->norm = vec();
		s->forms[i - P_SCENE]->col = col();
		e->s->nb_lights = (i - P_SCENE) + 1;
		return (check_light(e, s, i, 0));
	}
	else if (ft_strnstr(e->map[i], "plane=[", 7) != NULL)
	{
		set_form(s, i - P_SCENE, PLANE);
		s->forms[i - P_SCENE]->pos = vec();
		s->forms[i - P_SCENE]->norm = vec();
		s->forms[i - P_SCENE]->col = col();
		return (check_plane(e, s, i, 0));
	}
	else
		return (check_form2(e, s, i));
	return (1);
}

void		params_send(t_env *e, t_sce *s, int i)
{
	int		ret;

	s->coor = 0;
	ret = 0;
	if (i == 0)
		ret = check_name(e, s, 0);
	else if (i == 1)
		ret = check_camera(e, s, 1, 0);
	else if (i == 2)
		ret = check_intensity(e, s, 2, 0);
	else if (i == 3)
		ret = check_shadow(e, s, 3, 0);
	else if (i == 4)
		ret = check_shine(e, s, 4);
	else if (i > 4)
		ret = check_form(e, s, i);
	if (ret == 1)
	{
		ft_putstr("Syntax error at line : ");
		ft_putnbr(i + 1);
		ft_exit(". Exiting.");
	}
}

void		check_params(t_env *e, t_sce *s, int line_nb)
{
	int		i;

	if (line_nb < 6)
		ft_exit("Lines are missing in conf file or file is not valid.");
	if ((s->forms = (t_form**)malloc(sizeof(t_form*) * (line_nb - 5))) == 0)
		ft_exit("Error malloc forms.");
	i = 0;
	while (i < line_nb)
	{
		params_send(e, s, i);
		i++;
	}
	e->nb_forms = i - P_SCENE;
}
