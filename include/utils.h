#ifndef UTILS_H
# define UTILS_H

typedef struct s_dlst
{
	void			*content;
	struct s_dlst	*next;
	struct s_dlst	*prev;
}					t_dlst;

void	ms_print(int fd, char *color, char *str);
void	ms_print_lexem(void *str);

void	*kl_malloc(size_t size);
void	kl_end(char *str, int exit_code);
void	kl_free_arr(void *arr);
char	*kl_strdup_len(const char *str, size_t len);

t_dlst	*dlst_new(void *content);
void	dlst_add_front(t_dlst **s_dlst_src, t_dlst *s_dlst_new);
void	dlst_add_back(t_dlst **s_dlst_src, t_dlst *new);
void	dlst_map(t_dlst *s_dlst, void (*func)(void *));
void	dlst_end(t_dlst **s_dlst);

#endif //UTILS_H
