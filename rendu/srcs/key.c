/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaudin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 17:00:14 by ggaudin-          #+#    #+#             */
/*   Updated: 2018/03/06 14:25:27 by agaspard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

int			keyhook5(int k, int re, t_env *e)
{
	if ((k == K_T || k == K_G || k == K_F || k == K_H) && e->choice != -1)
	{
		if (k == K_H)
			e->s->forms[e->choice]->pos.x++;
		else if (k == K_F)
			e->s->forms[e->choice]->pos.x--;
		else if (k == K_T)
			e->s->forms[e->choice]->pos.y++;
		else if (k == K_G)
			e->s->forms[e->choice]->pos.y--;
		re++;
	}
	else if ((k == K_PLS || k == K_MIN) && e->choice != -1)
	{
		if (k == K_PLS)
			e->s->forms[e->choice]->rad++;
		else if (k == K_MIN)
			e->s->forms[e->choice]->rad = ((e->s->forms[e->choice]->rad -\
	1) < 1) ? e->s->forms[e->choice]->rad : e->s->forms[e->choice]->rad - 1;
		re++;
	}
	return (re + keyhook6(k, re, e));
}

int			keyhook4(int k, int re, t_env *e)
{
	if (k == K_W || k == K_A || k == K_S || k == K_D || \
			k == K_Z || k == K_X || k == K_L || k == K_U)
	{
		if (k == K_W)
			e->s->camy++;
		else if (k == K_S)
			e->s->camy--;
		else if (k == K_A)
			e->s->camx--;
		else if (k == K_D)
			e->s->camx++;
		else if (k == K_Z)
			e->s->camz++;
		else if (k == K_X)
			e->s->camz--;
		else if (k == K_U)
			e->s->anti = (e->s->anti == 0) ? 1 : 0;
		re++;
	}
	return (re + keyhook5(k, re, e));
}

int			keyhook3(int k, int re, t_env *e)
{
	if ((k == K_NUM_7 || k == K_NUM_8 || k == K_NUM_4 || \
			k == K_NUM_5 || k == K_NUM_1 || k == K_NUM_2) && e->choice != -1)
	{
		if (k == K_NUM_7)
			rotformz(e->s->forms[e->choice], 9);
		else if (k == K_NUM_8)
			rotformz(e->s->forms[e->choice], -9);
		else if (k == K_NUM_4)
			rotformx(e->s->forms[e->choice], 9);
		else if (k == K_NUM_5)
			rotformx(e->s->forms[e->choice], -9);
		else if (k == K_NUM_1)
			rotformy(e->s->forms[e->choice], 9);
		else if (k == K_NUM_2)
			rotformy(e->s->forms[e->choice], -9);
		re++;
	}
	return (re + keyhook4(k, re, e));
}

int			keyhook2(int k, int re, t_env *e)
{
	if (k == K_UP || k == K_DOWN || k == K_LEFT || \
			k == K_RIGHT || k == K_N || k == K_M)
	{
		if (k == K_LEFT)
			e->facty += 2;
		else if (k == K_RIGHT)
			e->facty -= 2;
		else if (k == K_UP)
			e->factx += 2;
		else if (k == K_DOWN)
			e->factx -= 2;
		else if (k == K_N)
			e->factz += 2;
		else if (k == K_M)
			e->factz -= 2;
		re++;
	}
	if (k == K_ESC)
		exit(EXIT_SUCCESS);
	return (re + keyhook3(k, re, e));
}

int			keyhook(int k, t_env *e)
{
	int		re;

	re = 0;
	if (k == K_L && e->rt_activate != 0)
	{
		e->lev++;
		if (e->lev > 2)
			e->lev = 0;
		re++;
	}
	if (k == K_RET && e->rt_activate != 0)
		export_image(e);
	if (k == 8 && e->rt_activate != 0)
		write_in_file(e);
	re += keyhook2(k, re, e) + keyhook7(k, re, e);
	if (re > 0)
	{
		mlx_clear_window(e->mlx, e->win);
		mlx_destroy_image(e->mlx, e->img);
		init_image(e);
		threads_launch(e);
	}
	return (0);
}
