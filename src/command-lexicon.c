/*
    command-lexicon.c
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
#include <ctype.h>

#include "token.h"
#include "command-lexicon.h"

int matchBye(token *tok, char **s)
{
	if (!strncasecmp(*s, "bye", 3))
	{
		tokenFill(tok, tokTypeClear, tokValueTypeNone, NULL, 0);
		*s += 3;
		return 1;
	}

	return 0;
}

int matchClear(token *tok, char **s)
{
	if (!strncasecmp(*s, "clear", 5))
	{
		tokenFill(tok, tokTypeClear, tokValueTypeNone, NULL, 0);
		*s += 5;
		return 1;
	}

	return 0;
}

int matchList(token *tok, char **s)
{
	if (!strncasecmp(*s, "list", 4))
	{
		tokenFill(tok, tokTypeList, tokValueTypeNone, NULL, 0);
		*s += 4;
		return 1;
	}

	return 0;
}

int matchRun(token *tok, char **s)
{
	if (!strncasecmp(*s, "run", 3))
	{
		tokenFill(tok, tokTypeRun, tokValueTypeNone, NULL, 0);
		*s += 3;
		return 1;
	}

	return 0;
}

int matchSize(token *tok, char **s)
{
	if (!strncasecmp(*s, "size", 4))
	{
		tokenFill(tok, tokTypeSize, tokValueTypeNone, NULL, 0);
		*s += 4;
		return 1;
	}

	return 0;
}

int matchFree(token *tok, char **s)
{
	if (!strncasecmp(*s, "free", 4))
	{
		tokenFill(tok, tokTypeFree, tokValueTypeNone, NULL, 0);
		*s += 4;
		return 1;
	}

	return 0;
}

