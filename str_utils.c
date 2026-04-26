#include "shell.h"

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: 0 if same, negative/positive difference if different
 */
int _strcmp(const char *s1, const char *s2)
{
	int i = 0;

	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;

	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/**
 * _strdup - duplicates a string into newly allocated memory
 * @str: string to duplicate
 *
 * Return: pointer to duplicated string, or NULL on failure
 */
char *_strdup(const char *str)
{
	char *copy;
	int i = 0;
	int len = 0;

	if (str == NULL)
		return (NULL);

	while (str[len] != '\0')
		len++;

	copy = malloc(sizeof(char) * (len + 1));
	if (copy == NULL)
		return (NULL);

	while (str[i] != '\0')
	{
		copy[i] = str[i];
		i++;
	}

	copy[i] = '\0';
	return (copy);
}

/**
 * _strcspn - gets length before first rejected character
 * @s: string to scan
 * @reject: rejected characters
 *
 * Return: number of characters before rejected character
 */
size_t _strcspn(const char *s, const char *reject)
{
	size_t i = 0;
	size_t j;

	while (s[i] != '\0')
	{
		j = 0;
		while (reject[j] != '\0')
		{
			if (s[i] == reject[j])
				return (i);
			j++;
		}
		i++;
	}

	return (i);
}

/**
 * _strchr - locates first occurrence of a character in a string
 * @s: string to search
 * @c: character to find
 *
 * Return: pointer to character, or NULL if not found
 */
char *_strchr(const char *s, int c)
{
	int i = 0;
	char ch = (char)c;

	while (s[i] != '\0')
	{
		if (s[i] == ch)
			return ((char *)&s[i]);
		i++;
	}

	if (ch == '\0')
		return ((char *)&s[i]);

	return (NULL);
}
