/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlajovec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:07:27 by jlajovec          #+#    #+#             */
/*   Updated: 2018/03/02 16:04:39 by jlajovec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

void		obj_spec(t_env *e, int obj_id, int i)
{
	e->s->forms[i]->form_id = obj_id;
	e->s->forms[i]->pos.x = 0;
	e->s->forms[i]->pos.y = -1;
	e->s->forms[i]->pos.z = -20;
	e->s->forms[i]->norm.x = 0;
	e->s->forms[i]->norm.y = 1;
	e->s->forms[i]->norm.z = 0;
	if (obj_id == SPHERE || obj_id == CYLINDER || obj_id == CONE)
		e->s->forms[i]->rad = 1;
	if (obj_id == CYLINDER || obj_id == CONE)
		e->s->forms[i]->high = 5;
	e->s->forms[i]->col.r = (rand()) / (float)RAND_MAX;
	e->s->forms[i]->col.g = (rand()) / (float)RAND_MAX;
	e->s->forms[i]->col.b = (rand()) / (float)RAND_MAX;
}

void		add_object(t_env *e, int obj_id)
{
	int		i;

	i = e->nb_forms + 1;
	ft_putnbr(e->nb_forms);
	if (!(e->s->forms = (t_form **)ft_realloc(e->s->forms,\
		sizeof(t_form *) * i)))
		ft_exit("Error.");
	if (!(e->s->forms[e->nb_forms] = (t_form *)malloc(sizeof(t_form))))
		ft_exit("Error.");
	obj_spec(e, obj_id, e->nb_forms);
	e->nb_forms++;
}
