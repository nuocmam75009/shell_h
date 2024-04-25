#include "shell.h"

/**
 * main - entry point for our simple shell program, checks for interactive
 *  or non-interactive
 * @argc: count of command line arguments
 * @argv: command line arguments array
 * Return: 0 if successful exit
*/

int main(int argc, char **argv)
{
	char *input_line; // store the line of input
	char *newline = "\n";
	(void)argc; // to cast it to a void type

	while (1) // (1) means loops until a break statement is encountered
			  // in shell, it allows the user to enter multiple commands continuously
	{
		prompt_and_read_input(&input_line);

		if (!input_line) //chekcs if input line is null
		{
			if (isatty(STDIN_FILENO)) //checks if standard input is a terminal with isatty
									  //if user types EOF commands like ctrl d
			{
				write(STDOUT_FILENO, newline, strlen(newline)); //writes a newline to the output using write func
			}
			break;
		}
		process_command(input_line, argv, environ); // calls func
		free(input_line);
	}

	return (0);
}
