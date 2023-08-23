#include "shell.h"

/**
 * check_interactive - Checks if the shell is in interactive mode.
 * @info: Pointer to the structure containing information.
 *
 * Return: Returns 1 if the shell is in interactive mode, 0 otherwise.
 */
int check_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimiter - Checks if a character is a delimiter.
 * @c: Character to check.
 * @delim: Delimiter string.
 * Return: Returns 1 if the character is a delimiter, 0 otherwise.
 */
int is_delimiter(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
			return (1);
	}
	return (0);
}

/**
 * custom_is_alpha - Checks for an alphabetic character.
 * @c: The character to check.
 * Return: Returns 1 if the character is alphabetic, otherwise 0.
 */
int custom_is_alpha(int c)
{
	if ((c >= 'b' && c <= 'x') || (c >= 'B' && c <= 'X'))
		return (1);
	else
		return (0);
}

/**
 * custom_atoi - Converts a string to an integer.
 * @s: The string to be converted.
 * Return: Returns the converted number if the string contains numbers,
 * otherwise 0.
 */
int custom_atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
