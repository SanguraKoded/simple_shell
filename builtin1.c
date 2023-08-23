#include "shell.h"

/**
 * display_history - Displays the history list, one command per line, preceded
 *                   by line numbers starting at 0.
 * @info: Pointer to the structure containing potential arguments. Used to
 *        maintain constant function prototype.
 * Return: Always returns 0.
 */
int display_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Unsets an alias by removing it from the alias list.
 * @info: Pointer to the structure containing potential arguments.
 * @str: String representing the alias to unset.
 * Return: Returns 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
	char *q, s;
	int ret;

	q = _strchr(str, '=');
	if (!q)
		return (1);
	s = *q;
	*q = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*q = s;
	return (ret);
}

/**
 * set_alias - Sets an alias by adding it to the alias list.
 * @info: Pointer to the structure containing potential arguments.
 * @str: String representing the alias to set.
 * Return: Returns 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
	char *q;

	q = _strchr(str, '=');
	if (!q)
		return (1);
	if (!*++q)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Prints an alias string.
 * @node: Pointer to the alias node to be printed.
 * Return: Returns 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
	char *q = NULL, *b = NULL;

	if (node)
	{
		q = _strchr(node->str, '=');
		for (b = node->str; b <= q; b++)
			_putchar(*b);
		_putchar('\'');
		_puts(q + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * manage_alias - Manages alias settings mimicking the alias builtin (man alias).
 * @info: Pointer to the structure containing arguments. Used to maintain constant
 *        function prototype.
 * Return: Always returns 0.
 */
int manage_alias(info_t *info)
{
	int i = 0;
	char *q = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		q = _strchr(info->argv[i], '=');
		if (q)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
