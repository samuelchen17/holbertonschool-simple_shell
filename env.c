#include "shell.h"

char **owned_environ;

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
 * valid_env_name - validates environment variable name
 * @name: variable name
 *
 * Return: 1 if valid, 0 if invalid
 */
int valid_env_name(const char *name)
{
	if (name == NULL || *name == '\0')
		return (0);

	if (strchr(name, '=') != NULL)
		return (0);

	return (1);
}

/**
 * count_env - counts environment variables
 *
 * Return: number of environment variables
 */
size_t count_env(void)
{
	size_t count = 0;

	while (environ[count] != NULL)
		count++;

	return (count);
}

/**
 * make_env_string - creates NAME=value string
 * @name: variable name
 * @value: variable value
 *
 * Return: malloc'd string, or NULL
 */
char *make_env_string(const char *name, const char *value)
{
	char *str;
	size_t i = 0;
	size_t j = 0;
	size_t name_len;
	size_t value_len;

	if (value == NULL)
		value = "";

	name_len = strlen(name);
	value_len = strlen(value);

	str = malloc(sizeof(char) * (name_len + value_len + 2));
	if (str == NULL)
		return (NULL);

	while (name[i] != '\0')
	{
		str[i] = name[i];
		i++;
	}

	str[i] = '=';
	i++;

	while (value[j] != '\0')
	{
		str[i] = value[j];
		i++;
		j++;
	}

	str[i] = '\0';
	return (str);
}

/**
 * env_name_matches - checks if env string matches name
 * @env: environment string
 * @name: variable name
 *
 * Return: 1 if match, 0 otherwise
 */
int env_name_matches(const char *env, const char *name)
{
	size_t len;

	len = strlen(name);

	if (strncmp(env, name, len) == 0 && env[len] == '=')
		return (1);

	return (0);
}

/**
 * print_environ - print all environment variables
 * @environ: environment variables
 */

void print_environ(char **environ)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
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
	size_t i = 0;
	size_t count;

	if (!valid_env_name(name))
		return (-1);

	if (copy_environment() == -1)
		return (-1);

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

	count = i;
	new_env = realloc(owned_environ, sizeof(char *) * (count + 2));
	if (new_env == NULL)
	{
		free(new_var);
		return (-1);
	}

	new_env[count] = new_var;
	new_env[count + 1] = NULL;
	owned_environ = new_env;
	environ = owned_environ;

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

/* the following functions are only purposed to ensure no mem leaks are inplace during setenv, as environ is a global variable from the parent rpocess and the child process does not ahve the ability to release it */
/**
 * free_environment - frees copied environment
 */
void free_environment(void)
{
	size_t i = 0;

	if (owned_environ == NULL)
		return;

	while (owned_environ[i] != NULL)
	{
		free(owned_environ[i]);
		i++;
	}

	free(owned_environ);
	owned_environ = NULL;
}

/* only if copy_environemtn fails half way*/
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
	char **new_env;
	size_t i = 0;
	size_t count;

	if (owned_environ != NULL)
		return (0);

	count = count_env();
	new_env = malloc(sizeof(char *) * (count + 1));
	if (new_env == NULL)
		return (-1);

	while (i < count)
	{
		new_env[i] = strdup(environ[i]);
		if (new_env[i] == NULL)
		{
			free_partial_env(new_env, i);
			return (-1);
		}
		i++;
	}

	new_env[count] = NULL;
	owned_environ = new_env;
	environ = owned_environ;

	return (0);
}
