/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaudin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 23:57:45 by ggaudin-          #+#    #+#             */
/*   Updated: 2018/02/26 19:25:28 by jlajovec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

void		levspecular(t_env *e)
{
	int		i;

	i = -1;
	while (++i < e->r[0]->nb_forms)
		if (e->r[0]->s->forms[i]->form_id == LIGHT)
		{
			lightset(e, i);
			norm_init(e);
			reflection(e);
			specular(e);
			fill_image(e);
		}
	e->r[0]->image[e->i][e->j].r *= e->r[0]->intensity;
	e->r[0]->image[e->i][e->j].g *= e->r[0]->intensity;
	e->r[0]->image[e->i][e->j].b *= e->r[0]->intensity;
}

void		levdiffuse(t_env *e, int i, t_vec tmp)
{
	lightset(e, i);
	e->p0 = vec_add(&e->rayo, &tmp);
	norm_init(e);
	diffuse(e);
}

static void	levels_2(t_env *e, int i)
{
	t_vec	tmp;

	tmp = prod_matr(e->mint, &e->raydir);
	e->red = 0;
	e->green = 0;
	e->blue = 0;
	while (++i < e->r[0]->s->nb_lights)
		levdiffuse(e, i, tmp);
	dark_image(e);
	if (e->r[0]->lev == 1)
		levspecular(e);
	if (e->r[0]->lev == 2)
		reflexion(e);
	save_col(e);
	if (e->r[0]->s->shadow == 1 && e->r[0]->lev != 2)
		shadow(e);
}

void		levels(t_env *e)
{
	int		i;

	i = -1;
	if (e->form_hit != -1)
	{
		e->r[0]->image[e->i][e->j].r = e->r[0]->s->forms[e->form_hit]->col.r;
		e->r[0]->image[e->i][e->j].g = e->r[0]->s->forms[e->form_hit]->col.g;
		e->r[0]->image[e->i][e->j].b = e->r[0]->s->forms[e->form_hit]->col.b;
		if (e->r[0]->lev >= 1)
		{
			levels_2(e, i);
		}
	}
}
