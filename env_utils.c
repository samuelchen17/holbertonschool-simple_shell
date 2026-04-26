#include "shell.h"

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
 * valid_env_name - validates environment variable name
 * @name: variable name
 *
 * Return: 1 if valid, 0 if invalid
 */
int valid_env_name(const char *name)
{
	if (name == NULL || *name == '\0')
		return (0);

	if (_strchr(name, '=') != NULL)
		return (0);

	return (1);
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
