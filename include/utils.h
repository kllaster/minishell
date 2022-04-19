#ifndef UTILS_H
# define UTILS_H

typedef struct s_list_var
{
	void		*var1;
	void		*var2;
}				t_list_var;

int		wait_process(pid_t pid);
int		dup_fd(int fd_new, int fd_old);

void	ms_print_cmd_error(char *cmd_name, char *error_str);
void	ms_print_lexemes(t_dlst *dlst_item);
void	ms_put_heredoc(void);
void	ms_put_tag(void);
void	ms_print(int fd, char *color, char *str);

#endif
