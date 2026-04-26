#include "shell.h"

/**
 * owned_env_ref - stores copied environment pointer
 *
 * Return: address of owned environment pointer
 */
char ***owned_env_ref(void)
{
	static char **owned_environ;

	return (&owned_environ);
}

/**
 * free_environment - frees copied environment
 */
void free_environment(void)
{
	char ***owned;
	size_t i = 0;

	owned = owned_env_ref();

	if (*owned == NULL)
		return;

	while ((*owned)[i] != NULL)
	{
		free((*owned)[i]);
		i++;
	}

	free(*owned);
	*owned = NULL;
}

/**
 * free_partial_env - frees partly copied environment
 * @env: environment array
 * @count: number of copied strings
 */
void free_partial_env(char **env, size_t count)
{
	while (count > 0)
	{
		count--;
		free(env[count]);
	}

	free(env);
}

/**
 * copy_environment - copies environ into owned memory
 *
 * Return: 0 on success, -1 on failure
 */
int copy_environment(void)
{
	char ***owned;
	char **new_env;
	size_t i = 0;
	size_t count;

	owned = owned_env_ref();

	if (*owned != NULL)
		return (0);

	count = count_env();
	new_env = malloc(sizeof(char *) * (count + 1));
	if (new_env == NULL)
		return (-1);

	while (i < count)
	{
		new_env[i] = _strdup(environ[i]);
		if (new_env[i] == NULL)
		{
			free_partial_env(new_env, i);
			return (-1);
		}
		i++;
	}

	new_env[count] = NULL;
	*owned = new_env;
	environ = *owned;

	return (0);
}
