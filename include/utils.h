#ifndef UTILS_H
# define UTILS_H

typedef struct		s_lst
{
	void			*content;
	struct s_lst	*next;
}					t_lst;

void	ms_print(int fd, char *color, char *str);

void	*kl_malloc(size_t size);
void	kl_end(char *str, int exit_code);
void	kl_free_arr(void *arr);

t_lst	*ft_lst_new(void *content);
void	ft_lst_add_front(t_lst **s_lst_src, t_lst *s_lst_new);
void	ft_lst_add_back(t_lst **s_lst_src, t_lst *new);
void	ft_lst_map(t_lst *s_lst, void (*func)(void *));

#endif //UTILS_H
