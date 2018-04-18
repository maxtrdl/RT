/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaudin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 22:25:20 by ggaudin-          #+#    #+#             */
/*   Updated: 2018/02/21 22:25:47 by ggaudin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

float		dot(t_vec a, t_vec b)
{
	float	ret;

	ret = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	return (ret);
}

t_vec		vec_sub(t_vec *a, t_vec *b)
{
	t_vec	src;

	src = vec();
	src.x = a->x - b->x;
	src.y = a->y - b->y;
	src.z = a->z - b->z;
	return (src);
}

t_vec		vec_add(t_vec *a, t_vec *b)
{
	t_vec	src;

	src = vec();
	src.x = a->x + b->x;
	src.y = a->y + b->y;
	src.z = a->z + b->z;
	return (src);
}

t_vec		prod_matr(float r, t_vec *m)
{
	t_vec	src;

	src = vec();
	src.x = r * m->x;
	src.y = r * m->y;
	src.z = r * m->z;
	return (src);
}

t_vec		vec_normalize(t_vec *v)
{
	float	lenvec;
	t_vec	tmp;

	tmp = vec();
	lenvec = sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z));
	tmp.x = v->x / lenvec;
	tmp.y = v->y / lenvec;
	tmp.z = v->z / lenvec;
	return (tmp);
}
