/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaudin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 23:19:55 by ggaudin-          #+#    #+#             */
/*   Updated: 2018/02/21 23:19:56 by ggaudin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

t_col	col(void)
{
	t_col	c;

	c.r = 0.00;
	c.g = 0.00;
	c.b = 0.00;
	return (c);
}

t_vec	vec(void)
{
	t_vec	v;

	v.x = 0.00;
	v.y = 0.00;
	v.z = 0.00;
	return (v);
}

void	init_main(t_env *e)
{
	e->more = 0;
	e->inits = 0;
	e->p0 = vec();
	e->diffusecol = col();
	e->speculcol = col();
}
