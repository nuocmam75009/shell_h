#include "shell.h"

/**
 * parse_input - Tokenizes an input line into an array of tokens.
 * @input_line: The input line to tokenize.
 * Description: This function takes an input line and breaks it into tokens
 * Return: A pointer to array of token. If memory allocation fails,
 * exit failure
 */

char **parse_input(char *input_line)
{
	// buffsize is used to keep track of allocated memory for the tokens
	//position is used to track the current position in the allocated memory for tokens
	int buffsize = 128, position = 0;
	// allocates enough memory to hold buffsize number of character pointers
	// the entire allocation is stored in the @tokens variable, which is now a double char pointer
	char **tokens = malloc(buffsize * sizeof(char *));
	// @token to store a single token from @input_line
	// @tokens_temp is temporary variable during memory allocation
	char *token, **tokens_temp;

	if (!tokens) //if memory allocation is unsuccessful
	{
		// exits with status EXIT_FAILURE
		fprintf(stderr, "Allocation error\n");
		exit(EXIT_FAILURE);
	}

	//strtok splits a string into substrings. here @input_line is the substring
	// the delimiters are t r n a -> any whitespace char
	// strtok modifies @input_line and returns a pointer to the first token.
	//-> the return value is stored in @token.
	token = strtok(input_line, " \t\r\n\a");

	while (token != NULL) // loop as long as @token isn't NULL
	{
		tokens[position++] = token; //increments @position to point to next available slot in @tokens array

		// next bloc is in case the buffer is full, it allocates twice the size using realloc
		if (position >= buffsize)
		{
			buffsize *= 2;
			//realloc resizes memory allocated to @tokens
			/// takes @tokens and the new size (buffsize * sizeof(char *)) as arguments
			tokens_temp = realloc(tokens, buffsize * sizeof(char *));


			if (!tokens_temp) // if allocation unsuccessful
			{
				free(tokens);
				fprintf(stderr, "Allocation error\n");
				exit(EXIT_FAILURE);
			}
			tokens = tokens_temp;
		}
		//to obtain remaining tokens and not only the first, need to pass NULL as first argument of strtok.
		// returns token until no token left
		token = strtok(NULL, " \t\r\n\a");
	}

	// marks the end of the @tokens array
	tokens[position] = NULL;
	return (tokens);
}
