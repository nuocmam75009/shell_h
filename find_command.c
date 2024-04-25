#include "shell.h"

/**
 * check_command_path - Checks if a command exists in a directory
 * @dir: Directory to check command
 * @command: Command
 * Return: Full path to command if found, NULL if not
 */
char *check_command_path(const char *dir, const char *command)
{
	char *full_path; //store full path of command
	struct stat statbuf; //information about a file stored in statbuf
	size_t length = strlen(dir) + strlen(command) + 2; //calculates required memory size for the full_path strng
	 												   //adds 2 for the slash /  between directory and command name and for the null terminator

	full_path = malloc(length); //allocates memory of calculated size for full_path
	if (!full_path) //if malloc unsuccessful
	{
		perror("malloc");
		return (NULL);
	}

	sprintf(full_path, "%s/%s", dir, command); //uses sprintf to construct the full path of command
	//sprintf is same as printf but instead of prints, stores in buffer pointed by @full_path
	//formats the string @full_path with %s (inserts string pointed to by @dir), / a,d %s (inserts string pointed to by @command)

	if (stat(full_path, &statbuf) == 0 && //checks if stat system call is successfull
		S_ISREG(statbuf.st_mode) && (statbuf.st_mode & S_IXUSR)) //checks if file is a regular fil, and then if user has execute permission
		 														 // S_IXUSR = execute permission for the user
	{
		return (full_path);
	}

	free(full_path);
	return (NULL);
}




/**
 * find_command_in_path - Searches for the command in PATH
 * @command: Command to find
 * Return: Path to command if found, NULL if not
 */

char *find_command_in_path(char *command)
{
	char *path, *path_copy, *token, *saveptr, *cmd_path = NULL;
	// @*cmd_path is command path
	size_t path_len;

	path = getenv("PATH"); //retrieves value of env variable named PATH and stores in @path
	if (!path)
	{
		return (NULL); //if retrieving failed
	}

	path_len = strlen(path) + 1; //calculates length of @path and adds 1
	path_copy = malloc(path_len); //allocates memory for @path_len
	if (!path_copy) //if the malloc failed
	{
		perror("malloc");
		return (NULL);
	}
	//????? A QUOI CA SERT CA FRERE
	strncpy(path_copy, path, path_len);


	for (token = strtok_r(path_copy, ":", &saveptr); token != NULL;
	// tokenizes @path_copy based on ":"
	// @saveptr will be used by strtok_r to store location where the next token starts after current one.
	// it's necessary to continue tokenization across multiple calls to strtok_r within loop
	// loops until token is not NULL (indicating there are more tokens)

	token = strtok_r(NULL, ":", &saveptr)) //search for command in each directory
	{
		cmd_path = check_command_path(token, command);
		//calls the check_command_path func with 2 args: @token (directory) and @command (command name user entered)
		if (cmd_path) // if valid path is found
		{
			break;
		}
	}

	free(path_copy);
	return (cmd_path);
}
