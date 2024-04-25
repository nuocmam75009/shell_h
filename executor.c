#include "shell.h"

/**
 * check_path_executable - Checks if the file at path is executable.
 * @path: The path to the file.
 * Return: 1 if the file is executable, 0 otherwise.
 */

int check_path_executable(const char *path)
{
	// uses the stat system call to get info about file
	// structure stores info retrieved by stat
	struct stat statbuf;

	if (stat(path, &statbuf) == 0)
	{
		//S_ISREG is a macro from stat() used to intepret values in a stat struct as returned from system call stat().
		// S_ISREG evaluates to true if argument is a regular file

		//checks: if file is a regular file (not dir, special file etc) && if owner of file has xcute permissions
		if (S_ISREG(statbuf.st_mode) && (statbuf.st_mode & S_IXUSR))
		{
			//if both conditions are true return 1 otherwise 0
			return (1);
		}
	}
	return (0);
}

/**
 * create_command_path - Creates a command path from the command input
 * @command: The command input user entered
 * Return: A pointer to the string containing the path, NULL if failed
 */

// char *command is argument that takes character pointer to the command string entered by user
char *create_command_path(char *command)
{

	//*cmd_path: path of command
	char *cmd_path = NULL;
	size_t len;

	// function checks if command starts with a /
	// if yes it assumes the command knows the full path
	// it calls check_path_executable to verify if file exists and executable
	// if executable, allocates memory for the path and copies the @command string in it
	if (command[0] == '/') // if first char is /, it's an absolute path
	//absolute path is the location of a file or directory specified from the root directory
	//-> complete path from start of filesystem to root directory
	{
		if (check_path_executable(command))
		{
			len = strlen(command) + 1; // calculates the length of command
			cmd_path = malloc(len); //allocates memory for the length
			if (!cmd_path)
			{
				perror("malloc");
				// if allocation unsuccessful
				return (NULL);
			}
			//if allocation successful, copies @command into @cmd_path
			strcpy(cmd_path, command);
		}
	}
	else // if doesn't start with /, uses find_command_in_path
	{
		cmd_path = find_command_in_path(command);
	}
	return (cmd_path);
}

/**
 * execute_in_child - Executes a command in the child process
 * @cmd_path: The path command to be executed
 * @parsed_command: The parsed command with all arguments
 * @env: The environment
 */








// performs an action that replaces the current process with a new program
void execute_in_child(char *cmd_path, char **parsed_command, char **env)
{
// first arg is path to program that needs to be executed
// second is a double char pointer that points to array of char pointers -> each element = part of the command
//third arg is the environment
	if (execve(cmd_path, parsed_command, env) == -1)
	{
		//execve is a system call to execute a program
		// cmd_path specifies path to prog to be executed
		// parsed_command = arguments passed to program
		// env is environment variable
		perror("execve"); //perror prints a error message
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
}








/**
 * execute_command - Forks the current process and executes a command
 * @parsed_command: The parsed command with all arguments
 * @program_name: The name of the program
 * @env: The environment
 */

// function forks a child process and executes a command in that child process
void execute_command(char **parsed_command, char *program_name, char **env)
{

	char *cmd_path = create_command_path(parsed_command[0]);
	// create_command_path takes first element of parsed_command (the command) and finds the path of executable file
	pid_t pid;
	int status;

	if (!cmd_path) //checks if null = command not found
	{
		fprintf(stderr, "%s: 1: %s: not found\n", program_name, parsed_command[0]);
		return;
	}

	pid = fork(); //calls foork system call to create a new process, stored in  @pid
	// parent process: pid will be positive int representing child pid
	// if in child process, pid = 0
	if (pid == -1) // if fork failed
	{
		perror("fork");
	}
	else if (pid == 0) // if child process
	{
		execute_in_child(cmd_path, parsed_command, env);
	}
	else //executes in the parent process only (pid is positive int)
	{
		waitpid(pid, &status, 0); // wait until child process terminates
		//&status is pointer to int that stores exit status of child process
		free(cmd_path);
	}
}
