#include "shell.h"

/**
 * _getenv - gets an environment variable value
 * @name: environment variable name
 *
 * Return: pointer to value, or NULL if not found
 */
char *_getenv(const char *name)
{
	size_t i = 0;
	size_t len;

	if (name == NULL || *name == '\0')
		return (NULL);

	len = strlen(name);
	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
		i++;
	}

	return (NULL);
}

/**
 * _setenv - changes or adds an environment variable
 * @name: variable name
 * @value: variable value
 * @overwrite: overwrite existing value if non-zero
 *
 * Return: 0 on success, -1 on failure
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	char **new_env;
	char *new_var;
	char ***owned;
	size_t i = 0;

	if (!valid_env_name(name))
		return (-1);
	if (copy_environment() == -1)
		return (-1);
	owned = owned_env_ref();
	new_var = make_env_string(name, value);
	if (new_var == NULL)
		return (-1);
	while (environ[i] != NULL)
	{
		if (env_name_matches(environ[i], name))
		{
			if (overwrite == 0)
			{
				free(new_var);
				return (0);
			}
			free(environ[i]);
			environ[i] = new_var;
			return (0);
		}
		i++;
	}
	new_env = _realloc(*owned, sizeof(char *) * (i + 1),
		sizeof(char *) * (i + 2));
	if (new_env == NULL)
	{
		free(new_var);
		return (-1);
	}
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	*owned = new_env;
	environ = *owned;
	return (0);
}

/**
 * _unsetenv - deletes an environment variable
 * @name: variable name
 *
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(const char *name)
{
	size_t i = 0;
	size_t j;

	if (!valid_env_name(name))
		return (-1);

	if (copy_environment() == -1)
		return (-1);

	while (environ[i] != NULL)
	{
		if (env_name_matches(environ[i], name))
		{
			free(environ[i]);

			j = i;
			while (environ[j] != NULL)
			{
				environ[j] = environ[j + 1];
				j++;
			}

			continue;
		}

		i++;
	}

	return (0);
}
