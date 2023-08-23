#include "shell.h"

/**
 * exit_shell - Exits the shell.
 * @info: Pointer to the structure containing arguments. Used to maintain
 *         constant function prototype.
 * Return: Exits with a given exit status (0) if info->argv[0] != "exit".
 */
int exit_shell(info_t *info)
{
	int exitcheck;

	if (info->argv[1]) /* Check if there is an exit argument */
	{
		exitcheck = custom_atoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = custom_atoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * change_directory - Changes the current directory.
 * @info: Pointer to the struct containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always returns 0.
 */
int change_directory(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: Handle this case? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: Handle this case? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "Can't change directory to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * help_info - Provides help information.
 * @info: Pointer to the structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always returns 0.
 */
int help_info(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("Help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* Temporary unused argument workaround */
	return (0);
}
