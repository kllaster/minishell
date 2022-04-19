#include "minishell.h"

t_dlst	*tokenize__iterator(t_dlst **tokens, t_dlst *lexemes,
							t_tokenizer *tknzer)
{
	int	iteration;

	iteration = tokenize__logic(tokens, lexemes, tknzer);
	if (iteration > 0)
	{
		free_tokenizer(tokens, lexemes, tknzer);
		return (NULL);
	}
	else if (iteration == -1)
		lexemes = lexemes->prev;
	if (lexemes)
		lexemes = lexemes->prev;
	return (lexemes);
}

t_dlst	*tokenize(t_dlst *lexemes)
{
	t_tokenizer	tknzer;
	t_dlst		**tokens;
	t_dlst		*tokens_res;

	ft_bzero(&tknzer, sizeof(tknzer));
	tokens = kl_malloc(sizeof(t_dlst **));
	*tokens = NULL;
	while (lexemes)
		lexemes = tokenize__iterator(tokens, lexemes, &tknzer);
	if (tknzer.cmd_now != NULL)
		dlst_add_front(tokens, dlst_new(tknzer.cmd_now));
	tokens_res = dlst_last_node(*tokens);
	free(tokens);
	return (tokens_res);
}
