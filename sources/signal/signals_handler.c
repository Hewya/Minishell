#include "minishell.h"

/* ctrl - C displays a new prompt on a new line
 * ctrl - D exits the shell
 * ctrl - \ does nothing
 */


/*
Interactive Mode: When the shell is awaiting user input, pressing Ctrl-C (SIGINT) will reset the prompt, while Ctrl-\ (SIGQUIT) will be ignored.i

Non-Interactive Mode: When the shell is running a command, both SIGINT and SIGQUIT will cause a new line to be printed but will not affect the running command.

Ignoring SIGQUIT: Ensures that the shell does not terminate or produce any unexpected behavior when Ctrl-\ is pressed.

*/

void	ctrlC_shell_wait(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_disapear()
{
	struct	sigaction	act;

	//initalise act;
	act.sa_handler = SIG_IN;
	sigaction(SIGQUIT, &act, NULL);
}

void	signal_handler_wait(void)
{
	struct	sigaction act;

	sigquit_disapear();
	//Initialise the act structure to zero
	act.handler = &ctrl_c_handler;
	sigaction(SIGINT, &act, NULL);
}

void	new_line(int sig)
{
	(void)sig;
	rl_on_new_line();
}

void	signal_handler_run(void)
{
	struct sigaction act;

	//itialise struct act
	act.sa_handler = &new_line;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
