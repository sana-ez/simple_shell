
#include "shell.h"


/**
 * _myhistory - Display  history list, one command by line, preceded
 * With the line numbers, starting at 0.
 * @info: The structure containing potential arguments. Used to maintain
 * The constant function prototype.
 * return: Always 0
 */
int _myhistory(info_t *info)
{
print_list(info->history);
return (0);
}
/**
 * unset_alias - Sets the  alias to string
 * @info: The Parameter struct
 * @str: String alias
 *
 * return: Always 0 on success, 1 on error
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
 * set_alias - This is  the  code that  set alias to string
 * @info: The  parameter structure
 * @str: The String alias
 *
 * return: on success 0, on error 1
 */

int set_alias(info_t *info, char *str)
{
char *p;

p = _strchr(str, '=');
if (!p)
return (1);
if (!*++p)
return (unset_alias(info, str));

unset_alias(info, str);
return (add_node_end(&(info->alias), str, 0) == NULL);
}
/**
 * print_alias - Print an alias string
 * @node:  Alias node
 *
 * return: always 0 on success, 1 on error
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
 * _myalias - mimics  alias builtin (man alias)
 * @info: The structure containing potential arguments. Used to maintain
 *  The constant function prototype.
 *  return: Always 0
 */

int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
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
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}


