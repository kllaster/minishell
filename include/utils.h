#ifndef UTILS_H
# define UTILS_H

typedef struct s_list_var
{
	void		*var1;
	void		*var2;
}				t_list_var;

typedef struct s_shell_codes
{
	int         pid;
	int         is_exit;
	int         is_signal_code;
	int         exit_code;
	int         last_pcode;
}				t_shell_codes;

int	    wait_process(pid_t pid);
int	    dup_fd(int fd_new, int fd_old);

void    init_shell(void);
int     get_shell_exit(void);
int     get_shell_exit_code(void);
int     get_shell_pcode();
int     shell_pcode_is_signal(void);
void    set_shell_is_signal(int state);
void    set_shell_exit(int code);
void    set_shell_pcode(int code);
void    set_shell_pid(int pid);

void    signal_int(int code);
void    signal_quit(int code);

void	ms_print_cmd_error(char *cmd_name, char *error_str);
void	ms_print_lexemes(t_dlst *dlst_item);
void	ms_put_heredoc(void);
void	ms_put_tag(void);
void	ms_print_welcome(void);
void	ms_print(int fd, char *color, char *str);

#endif
