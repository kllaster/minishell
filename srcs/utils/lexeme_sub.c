#include "minishell.h"

t_lexeme	*new_lexeme(t_operator type, char *str, void (*validate)())
{
	t_lexeme	*lexeme;

	lexeme = kl_malloc(sizeof(t_lexeme));
	lexeme->type = type;
	lexeme->str = str;
	lexeme->validate = validate;
	return (lexeme);
}
