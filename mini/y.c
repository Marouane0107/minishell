#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "minishell.h"
int i = 0;
void	sigint_handler(int sig)
{
	(void)sig;
	// if(!global.g)
	write(1, "\n", 1);
    rl_replace_line("", 0);
	rl_on_new_line();
    rl_redisplay();
}
void her(int sig)
{
   (void)sig;
    i = 1;
    rl_replace_line("", 0); // Clear the input line
    rl_on_new_line(); // Move to a new line
    rl_redisplay(); // Redisplay the prompt
    close(0);
}
void t()
{
    int m;
    char *p;
    m = dup(0);
    signal(SIGINT, her);
    while(!i)
    {
       p =  readline("her$ ");
       if(!p)
        break;
        printf("gdf\n");
    }
    dup2(m, 0);
    close(m);
    signal(SIGINT, sigint_handler);
    i =0;
}
void	parss(void)
{
	char	*input;
	input = NULL;
	while (1)
	{
		signal(SIGINT, sigint_handler);
		input = readline("minishell$ ");
		if (!input)
			exit(1);
        t();
		add_history(input);
		if(strcmp(input, "exit") == 0)
			exit(0);
	}
}
int main()
{
    parss();
}