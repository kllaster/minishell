#include "minishell.h"

t_dlst	*dlst_new(void *content)
{
	t_dlst	*s_dlst;

	s_dlst = kl_malloc(sizeof(t_dlst));
	s_dlst->content = content;
	s_dlst->next = NULL;
	s_dlst->prev = NULL;
	return (s_dlst);
}

void	dlst_add_front(t_dlst **s_dlst_src, t_dlst *s_dlst_new)
{
	if ((*s_dlst_src) == NULL)
	{
		*s_dlst_src = s_dlst_new;
		return ;
	}
	s_dlst_new->next = *s_dlst_src;
	(*s_dlst_src)->prev = s_dlst_new;
	*s_dlst_src = s_dlst_new;
}

void	dlst_add_back(t_dlst **s_dlst_src, t_dlst *s_dlst_new)
{
	t_dlst	*s_dlst_last;

	if ((*s_dlst_src) == NULL)
	{
		*s_dlst_src = s_dlst_new;
		return ;
	}
	s_dlst_last = *s_dlst_src;
	while (s_dlst_last->next)
		s_dlst_last = s_dlst_last->next;
	s_dlst_last->next = s_dlst_new;
}

void	dlst_end(t_dlst **s_dlst)
{
	t_dlst	*last;

	last = *s_dlst;
	while (last->next)
		last = last->next;
	last->next = *s_dlst;
	(*s_dlst)->prev = last;
}

void	dlst_map(t_dlst *s_dlst, void (*func)(void *))
{
	t_dlst	*s_dlst_prev;

	if (s_dlst == NULL)
		return ;
	s_dlst_prev = s_dlst->prev;
	while (s_dlst != s_dlst_prev
		&& (s_dlst_prev && s_dlst != s_dlst_prev->prev))
	{
		func(s_dlst->content);
		s_dlst = s_dlst->next;
		if (s_dlst_prev != NULL)
		{
			func(s_dlst_prev->content);
			s_dlst_prev = s_dlst_prev->prev;
		}
	}
	func(s_dlst->content);
	if ((s_dlst_prev && s_dlst == s_dlst_prev->prev)
		&& s_dlst != s_dlst_prev)
		func(s_dlst_prev->content);
}
