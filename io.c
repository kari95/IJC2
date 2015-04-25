// io.c
// IJC-DU2
// Author: Miroslav Karásek, FIT
// Date: 2015-04-18

#include <ctype.h>
#include <stdio.h>
#include "io.h"

int fgetw(char *s, int max, FILE *f)
{
	int ch;
	int state = 0;
	int i = 0;
	while ((ch = fgetc(f)) != EOF)
	{
		if (state == 0) 
			if (!isspace(ch))
				state = 1;
		if (state == 1) 
		{
			if (!isspace(ch))
			{
				if (i < max - 1)
					s[i] = ch;
				i++;
			}
			else
				break;
		}
	}
	if (i < max)
		s[i] = '\0';
	else
		s[max - 1] = '\0';
	if (ch == EOF)
		return EOF;
	return i;
}