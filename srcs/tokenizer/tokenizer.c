#include "minishell.h"

t_dlst	*tokenize__iterator(t_dlst **tokens, t_dlst *lexemes,
							t_tokenizer *tknzer)
{
	int	iteration_res;

	iteration_res = tokenize__logic(tokens, lexemes, tknzer);
	if (iteration_res > 0)
	{
		free_tokenizer(tokens, lexemes, tknzer);
		return (NULL);
	}
	else if (iteration_res == -1)
		lexemes = lexemes->prev;
	if (lexemes)
		lexemes = lexemes->prev;
	return (lexemes);
}

t_dlst	*tokenize(t_dlst *lexemes)
{
	t_tokenizer	tknzer;
	t_dlst		*tokens;

	ft_bzero(&tknzer, sizeof(t_tokenizer));
	tokens = NULL;
	while (lexemes)
		lexemes = tokenize__iterator(&tokens, lexemes, &tknzer);
	if (tknzer.cmd_now != NULL)
		dlst_add_front(&tokens, dlst_new(tknzer.cmd_now));
	tokens = dlst_last_node(tokens);
	return (tokens);
}
