#include "shell.h"

/**
 * build_path - build full path name for command
 * @token: directory path
 * @cmd: command input from user
 *
 * Return: full path to executable, NULL if not found
 */
char *build_path(char *token, char *cmd)
{
	char *path;
	size_t len;

	len = strlen(token) + strlen(cmd) + 2;

	path = malloc(len);
	if (!path)
	{
		return (NULL);
	}

	/* build the path */
	strcpy(path, token);
	strcat(path, "/");
	strcat(path, cmd);

	return (path);
}

/**
 * lookup_path - check if path exists
 * @cmd: command input from user
 *
 * Return: full path to executable, NULL if not found
 */

char *lookup_path(char *cmd)
{
	char *token;
	char *path;
	char *tmp;
	char *cmd_path = NULL;
	struct stat file_info;

	path = _getenv("PATH");
	if (!path || path[0] == '\0')
		return (NULL);

	tmp = _strdup(path);
	if (!tmp)
		return (NULL);

	token = strtok(tmp, ":");

	while (token)
	{
		cmd_path = build_path(token, cmd);
		if (!cmd_path)
		{
			free(tmp);
			return (NULL);
		}

		/* check if path exists */
		if (stat(cmd_path, &file_info) == 0)
		{
			free(tmp);
			return (cmd_path);
		}

		free(cmd_path);
		cmd_path = NULL;

		token = strtok(NULL, ":");
	}

	free(tmp);
	return (NULL);
}

/**
 * handle_path - check if path exists for execution
 * @cmd: command input from user
 *
 * Return: full path to executable, NULL if not found
 */

char *handle_path(char *cmd)
{
	/* if direct command, check if executable */
	if (_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (_strdup(cmd));

		return (NULL);
	}

	return (lookup_path(cmd));
}

/**
 * free_path_list - frees PATH linked list
 * @head: list head
 *
 * Return: void
 */
void free_path_list(path_node_t *head)
{
	path_node_t *temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->dir);
		free(temp);
	}
}


/**
 * add_node_end - adds a PATH directory node to the end of a list
 * @head: pointer to the head of the list
 * @dir: directory string to store
 *
 * Return: new node, or NULL on failure
 */
path_node_t *add_node_end(path_node_t **head, char *dir)
{
	path_node_t *new_node;
	path_node_t *temp;

	if (head == NULL || dir == NULL)
		return (NULL);

	new_node = malloc(sizeof(path_node_t));
	if (new_node == NULL)
		return (NULL);

	new_node->dir = _strdup(dir);
	if (new_node->dir == NULL)
	{
		free(new_node);
		return (NULL);
	}

	new_node->next = NULL;

	if (*head == NULL)
	{
		*head = new_node;
		return (new_node);
	}

	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;

	temp->next = new_node;
	return (new_node);
}
