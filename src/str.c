/**
 * _strncmp - Compares two strings up to n bytes
 * @s1: First string to compare
 * @s2: Second string to compare
 * @n: Maximum number of bytes to compare
 *
 * Return: 0 if strings are equal, negative if s1 < s2, positive if s1 > s2
 */
int _strncmp(const char *s1, const char *s2, size_t n)
 {
	 size_t i;
	 /* Protection contre les pointeurs NULL */
	if (s1 == NULL && s2 == NULL)
		return (0);
	if (s1 == NULL)
		return (-1);
	if (s2 == NULL)
		return (1);
	 /* Comparaison caractère par caractère jusqu'à n */
	for (i = 0; i < n; i++)
	{
		 /* Si les caractères sont différents */
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		 /* Si on atteint la fin d'une des chaînes */
		if (s1[i] == '\0')
			return (0);  /* Les deux sont égales jusqu'ici */
	 }
	 /* Si on a comparé exactement n caractères */
	return (0);
}

#include "main.h"
#include <stdio.h>
/**
*_strchr - prototype string character
*@s: pointeurs variable
*@c: variable
*Return: my count
*/

char *_strchr(char *s, char c)

{

while (*s)
{
	if (*s == c)
		return (s);
		s++;
}

if (c == '\0')
	return (s);

return (NULL);

}

#include "main.h"
#include <string.h>
/**
*_strlen - calculate the length of a string
*@s : variable into prototype
*Return: the length of the string (excluding the null terminator)
*/

int _strlen(char *s)
{

int length = 0;

	while (s[length] != '\0')
	{
	length++;
	}

return (length);

}


