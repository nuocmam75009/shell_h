#include "shell.h"

/**
 * is_empty - checks if the string is empty or contain whitespace
 * @str: string to verify
 * Return: one
 */

int is_empty(const char *str)
{
	while (*str != '\0') //loops until the character pointed to by @str is not null terminator
	{
		if (*str != ' ' && *str != '\t' && *str != '\n' && //checks if current character is not whitespace
			*str != '\r' && *str != '\f' && *str != '\v')
			return (0);
		str++;
	}
	return (1);
}
