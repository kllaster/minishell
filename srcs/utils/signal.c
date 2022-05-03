#include "minishell.h"

static t_shell_codes* get_shell()
{
	static t_shell_codes shell;
	return &shell;
}

void init_shell()
{
	t_shell_codes* shell;

	shell = get_shell();
	shell->pid = 0;
	shell->is_exit = 0;
	shell->is_signal_code = 0;
	shell->exit_code = 0;
	shell->last_pcode = 0;
}

int get_shell_pid()
{
	t_shell_codes* shell;

	shell = get_shell();
	return shell->pid;
}

int get_shell_exit()
{
	t_shell_codes* shell;

	shell = get_shell();
	return shell->is_exit;
}

int shell_pcode_is_signal(void)
{
	t_shell_codes* shell;

	shell = get_shell();
	return (shell->is_signal_code == 0 ? 0 : 1);
}

int get_shell_exit_code()
{
	t_shell_codes* shell;

	shell = get_shell();
	return (shell->exit_code);
}

int get_shell_pcode()
{
	t_shell_codes* shell;

	shell = get_shell();
	return shell->last_pcode;
}

void set_shell_exit(int code)
{
	t_shell_codes* shell;

	shell = get_shell();
	shell->is_exit = 1;
	shell->exit_code = code;
}

void set_shell_is_signal(int state)
{
	t_shell_codes* shell;

	shell = get_shell();
	shell->is_signal_code = state;
}

void set_shell_pid(int pid)
{
	t_shell_codes* shell;

	shell = get_shell();
	shell->pid = pid;
}

void set_shell_pcode(int code)
{
	t_shell_codes* shell;

	shell = get_shell();
	shell->last_pcode = code;
}

void signal_int(int code)
{
	(void)code;
	if (get_shell_pid() != 0)
	{
		set_shell_is_signal(1);
		set_shell_pcode(130);
	}
	else
		set_shell_pcode(1);
}

void signal_quit(int code)
{
	(void)code;
	if (get_shell_pid() != 0)
	{
		set_shell_is_signal(1);
		set_shell_pcode(131);
	}
}