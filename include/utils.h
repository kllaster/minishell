#ifndef UTILS_H
# define UTILS_H

typedef struct s_list_var
{
	void		*var1;
	void		*var2;
}				t_list_var;

void	ms_print(int fd, char *color, char *str);
void	ms_print_tokens(t_dlst *dlst_item);
void	ms_put_tag(void);

#endif
