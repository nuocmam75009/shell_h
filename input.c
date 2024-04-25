#include "shell.h"

/**
 * read_user_input - reads a line from stedin, allocates memory for it
 * Return: input
 */

char *read_user_input(void)
{
	char *input = NULL; // store user's input string
	size_t buffer_size = 0; // init buffer to 0
	ssize_t characters; //store number of characters read by getline

	characters = getline(&input, &buffer_size, stdin);
	//getline() is func for reading a string of text
	// getline will allocate memory and store adress of first char of allocated memory in &input
	// if line is longer than allocated buffer, getline will realloc with new size
	// stdin is where user type input

	if (characters == -1) // if getline encounters error
	{
		free(input);
		if (feof(stdin)) //checks if end of fiile indicator is set
		{
			exit(EXIT_SUCCESS); //if EOF is reached (ctrl d entered by user) then it's TRUE
		}
		else //error but not EOF
		{
			perror("read_user_input");
			exit(EXIT_FAILURE);
		}
	}
	return (input);
}

// read_user_input dynamically allocates memory to store the user's input line using getline
// handles potential errors and EOF conditions
// if successful, returns a pointer to allocated memory containing the user's input