/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflexion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaudin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 20:33:40 by ggaudin-          #+#    #+#             */
/*   Updated: 2018/03/06 17:56:18 by agaspard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"
#include <stdio.h>

static void		set_col(t_env *e, int j, t_vec newstart, int currshp)
{
	t_form	currlight;
	t_vec	light_dir;
	t_vec	dist;
	float	lambert;

	currlight = *e->r[0]->s->forms[j];
	round_num(&newstart);
	dist = vec_sub(&currlight.pos, &newstart);
	if (dot(e->n_ref, dist) > 0.0f)
	{
		e->t0 = sqrtf(dot(dist, dist));
		if (e->t0 > 0.000001f)
		{
			light_dir = prod_matr((1 / e->t0), &dist);
			lambert = dot(light_dir, e->n_ref) * e->coef_ref;
			e->color_ref.r += lambert * currlight.col.r \
						* e->r[0]->s->forms[currshp]->col.r;
			e->color_ref.g += lambert * currlight.col.g \
						* e->r[0]->s->forms[currshp]->col.g;
			e->color_ref.b += lambert * currlight.col.b \
						* e->r[0]->s->forms[currshp]->col.b;
		}
	}
}

static void		reflexion2(t_env *e, int currshp)
{
	int		j;
	t_vec	tempvec;
	t_vec	newstart;
	t_vec	temp;
	float	reflet;

	e->n_ref = vec();
	e->t0 = e->mint;
	tempvec = prod_matr(e->t0, &e->raydir);
	newstart = vec_add(&e->rayo, &tempvec);
	e->n_ref = getnorm(e, newstart, currshp, &tempvec);
	if (dot(e->n_ref, e->n_ref) == 0.0f)
		return ;
	e->n_ref = prod_matr((1.0f / sqrtf(dot(e->n_ref, e->n_ref))), &e->n_ref);
	j = -1;
	while (++j < e->r[0]->s->nb_lights)
		set_col(e, j, newstart, currshp);
	e->coef_ref *= 0.5;
	reflet = 2.0f * dot(e->raydir, e->n_ref);
	e->rayo = newstart;
	temp = prod_matr(reflet, &e->n_ref);
	e->raydir = vec_sub(&e->raydir, &temp);
	e->r[0]->image[e->i][e->j].r = e->color_ref.r;
	e->r[0]->image[e->i][e->j].g = e->color_ref.g;
	e->r[0]->image[e->i][e->j].b = e->color_ref.b;
}

static void		check_t0(t_env *e, int *currshp, int i)
{
	if (e->t0 < 0.0f)
	{
		e->t0 = INFINITY;
		e->mint = INFINITY;
	}
	if (e->t0 < e->mint && e->t0 > 0.0f)
	{
		e->mint = e->t0;
		*currshp = i;
	}
}

void			reflexion(t_env *e)
{
	int		level;
	int		currshp;
	int		i;

	e->color_ref = col();
	e->coef_ref = e->r[0]->reflet;
	level = -1;
	while ((e->coef_ref > 0.0f) && (++level < 2))
	{
		currshp = -1;
		e->t0 = INFINITY;
		e->mint = INFINITY;
		i = (e->r[0]->s->nb_lights - 1);
		while (++i < e->r[0]->nb_forms)
			if ((intersect(e, &e->rayo, &e->raydir, e->r[0]->s->forms[i])) == 1)
				check_t0(e, &currshp, i);
		if (currshp > -1)
		{
			reflexion2(e, currshp);
			if (level == 0 && e->r[0]->s->forms[currshp]->form_id == PLANE)
				return ;
		}
	}
}
