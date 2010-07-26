/*
    token.c
    Copyright (C) 2010  Patrick Head

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include <string.h>

#include "token.h"

void tokenFill(token *tok,
							 tokenType type,
							 tokenValueType valueType,
							 char *value,
							 int valueLength)
{
	char numberString[10];

	if (!tok) return;

	memset(numberString, 0, 10);

	tokenClear(tok);

	tok->type = type;
	tok->valueType = valueType;

	switch (valueType)
	{
		case tokValueTypeNone:
			break;
		case tokValueTypeString:
			tok->s = (char *)malloc(valueLength + 1);
			memset(tok->s, 0, valueLength + 1);
			strncpy(tok->s, value, valueLength);
			break;
		case tokValueTypeCharacter:
			tok->c = *value;
			break;
		case tokValueTypeNumber:
			strncpy(numberString, value, valueLength);
			tok->n = atoi(numberString);
			break;
	}

	return;
}

void tokenClear(token *tok)
{
	if (!tok) return;

	switch (tok->valueType)
	{
		case tokValueTypeString:
			if (tok->s) free(tok->s);
			break;
		case tokValueTypeNone:
		case tokValueTypeNumber:
		case tokValueTypeCharacter:
			break;
	}

	memset(tok, 0, sizeof(token));

	return;
}

