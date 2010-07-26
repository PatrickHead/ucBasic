/*
    language-lexicon.c
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

#include "language-lexicon.h"

int matchEOL(token *tok, char **s)
{
	if (**s == '\n')
	{
		tokenFill(tok, tokTypeEOL, tokValueTypeNone, NULL, 0);
		++*s;
		return 1;
	}

	return 0;
}

int matchComma(token *tok, char **s)
{
	if (**s == ',')
	{
		tokenFill(tok, tokTypeComma, tokValueTypeNone, NULL, 0);
		++*s;
		return 1;
	}

	return 0;
}

int matchNumber(token *tok, char **s)
{
	char *t = *s;

	while (isdigit(*t)) ++t;

	if (t != *s)
	{
		tokenFill(tok, tokTypeNumber, tokValueTypeNumber, *s, t - *s);
		*s += t - *s;
		return 1;
	}

	return 0;
}

int matchWhiteSpace(token *tok, char **s)
{
	char *t = *s;

	while ((*t == ' ') || (*t == '\t')) ++t;

	if (t != *s)
	{
		tokenFill(tok, tokTypeWhiteSpace, tokValueTypeNone, NULL, 0);
		*s += t - *s;
		return 1;
	}

	return 0;
}

int matchString(token *tok, char **s)
{
	char *t = *s;
	token testToken;
	int len = 0;

	while (!matchEOL(&testToken, &t)) ++t;

	len = t - *s - 1;

	tokenFill(tok, tokTypeString, tokValueTypeString, *s, len);

	*s += len;

	return 1;
}

int matchCharacterString(token *tok, char **s)
{
	char *t;
	token testToken;
	int i, len;
	char string[81];

	memset(string, 0, 81);

	for (len = i = 0, t = *s;;)
	{
		while (!matchDoubleQuote(&testToken, &t))
		{
			if (matchEOL(&testToken, &t)) return 0;
			string[i] = *t;
			++t;
			++len;
			++i;
		}

		if (!matchDoubleQuote(&testToken, &t))
		{
			--t;
			break;
		}

		string[i] = '"';

		len += 2;
		++i;
	}

	tokenFill(tok, tokTypeCharacterString, tokValueTypeString, string, i);

	*s += len;

	return 1;
}

int matchDoubleQuote(token *tok, char **s)
{
	if (**s == '"')
	{
		tokenFill(tok, tokTypeDoubleQuote, tokValueTypeNone, NULL, 0);
		*s += 1;
		return 1;
	}

	return 0;
}

int matchPrint(token *tok, char **s)
{
	if (!strncasecmp(*s, "print", 5))
	{
		tokenFill(tok, tokTypePrint, tokValueTypeNone, NULL, 0);
		*s += 5;
		return 1;
	}

	return 0;
}

int matchInput(token *tok, char **s)
{
	if (!strncasecmp(*s, "input", 5))
	{
		tokenFill(tok, tokTypeInput, tokValueTypeNone, NULL, 0);
		*s += 5;
		return 1;
	}

	return 0;
}

int matchLet(token *tok, char **s)
{
	if (!strncasecmp(*s, "let", 3))
	{
		tokenFill(tok, tokTypeLet, tokValueTypeNone, NULL, 0);
		*s += 3;
		return 1;
	}

	return 0;
}

int matchGoto(token *tok, char **s)
{
	if (!strncasecmp(*s, "goto", 4))
	{
		tokenFill(tok, tokTypeGoto, tokValueTypeNone, NULL, 0);
		*s += 4;
		return 1;
	}

	return 0;
}

int matchGosub(token *tok, char **s)
{
	if (!strncasecmp(*s, "gosub", 5))
	{
		tokenFill(tok, tokTypeGosub, tokValueTypeNone, NULL, 0);
		*s += 5;
		return 1;
	}

	return 0;
}

int matchReturn(token *tok, char **s)
{
	if (!strncasecmp(*s, "return", 6))
	{
		tokenFill(tok, tokTypeReturn, tokValueTypeNone, NULL, 0);
		*s += 6;
		return 1;
	}

	return 0;
}

int matchIf(token *tok, char **s)
{
	if (!strncasecmp(*s, "if", 2))
	{
		tokenFill(tok, tokTypeIf, tokValueTypeNone, NULL, 0);
		*s += 2;
		return 1;
	}

	return 0;
}

int matchThen(token *tok, char **s)
{
	if (!strncasecmp(*s, "then", 4))
	{
		tokenFill(tok, tokTypeThen, tokValueTypeNone, NULL, 0);
		*s += 4;
		return 1;
	}

	return 0;
}

int matchRemark(token *tok, char **s)
{
	if (!strncasecmp(*s, "rem", 3))
	{
		tokenFill(tok, tokTypeRemark, tokValueTypeNone, NULL, 0);
		*s += 3;
		return 1;
	}

	return 0;
}

int matchFunction(token *tok, char **s)
{
	if (matchFunctionCall(tok, s)) return 1;
	if (matchFunctionPeek(tok, s)) return 1;

	return 0;
}

int matchFunctionCall(token *tok, char **s)
{
	if (!strncasecmp(*s, "call", 4))
	{
		tokenFill(tok, tokTypeFunctionCall, tokValueTypeNone, NULL, 0);
		*s += 4;
		return 1;
	}

	return 0;
}

int matchFunctionPeek(token *tok, char **s)
{
	if (!strncasecmp(*s, "peek", 4))
	{
		tokenFill(tok, tokTypeFunctionPeek, tokValueTypeNone, NULL, 0);
		*s += 4;
		return 1;
	}

	return 0;
}

int matchLeftParenthesis(token *tok, char **s)
{
	if (**s == '(')
	{
		tokenFill(tok, tokTypeLeftParenthesis, tokValueTypeNone, NULL, 0);
		++*s;
		return 1;
	}

	return 0;
}

int matchRightParenthesis(token *tok, char **s)
{
	if (**s == ')')
	{
		tokenFill(tok, tokTypeRightParenthesis, tokValueTypeNone, NULL, 0);
		++*s;
		return 1;
	}

	return 0;
}

int matchSeparator(token *tok, char **s)
{
	if (matchComma(tok, s)) return 1;
	else if (matchSemicolon(tok, s)) return 1;

	return 0;
}

int matchSemicolon(token *tok, char **s)
{
	if (**s == ';')
	{
		tokenFill(tok, tokTypeSemicolon, tokValueTypeNone, NULL, 0);
		++*s;
		return 1;
	}

	return 0;
}

int matchColon(token *tok, char **s)
{
	if (**s == ':')
	{
		tokenFill(tok, tokTypeColon, tokValueTypeNone, NULL, 0);
		++*s;
		return 1;
	}

	return 0;
}

int matchVariable(token *tok, char **s)
{
	if (isalpha(**s))
	{
		tokenFill(tok, tokTypeVariable, tokValueTypeCharacter, *s, 1);
		++*s;
		return 1;
	}

	return 0;
}

int matchRelationalOperator(token *tok, char **s)
{
	if (matchLessThanOrEquals(tok, s)) return 1;
	if (matchGreaterThanOrEquals(tok, s)) return 1;
	if (matchNotEquals(tok, s)) return 1;
	if (matchLessThan(tok, s)) return 1;
	if (matchGreaterThan(tok, s)) return 1;
	if (matchEquals(tok, s)) return 1;

	return 0;
}

int matchLessThan(token *tok, char **s)
{
	if (**s == '<')
	{
		tokenFill(tok, tokTypeLessThan, tokValueTypeNone, NULL, 0);
		++*s;
		return 1;
	}

	return 0;
}

int matchGreaterThan(token *tok, char **s)
{
	if (**s == '>')
	{
		tokenFill(tok, tokTypeGreaterThan, tokValueTypeNone, NULL, 0);
		++*s;
		return 1;
	}

	return 0;
}

int matchEquals(token *tok, char **s)
{
	if (**s == '=')
	{
		tokenFill(tok, tokTypeEquals, tokValueTypeNone, NULL, 0);
		++*s;
		return 1;
	}

	return 0;
}

int matchLessThanOrEquals(token *tok, char **s)
{
	if (!strncasecmp(*s, "<=", 2))
	{
		tokenFill(tok, tokTypeLessThanOrEquals, tokValueTypeNone, NULL, 0);
		*s += 2;
		return 1;
	}

	return 0;
}

int matchGreaterThanOrEquals(token *tok, char **s)
{
	if (!strncasecmp(*s, ">=", 2))
	{
		tokenFill(tok, tokTypeGreaterThanOrEquals, tokValueTypeNone, NULL, 0);
		*s += 2;
		return 1;
	}

	return 0;
}

int matchNotEquals(token *tok, char **s)
{
	if (!strncasecmp(*s, "<>", 2) || !strncasecmp(*s, "><", 2))
	{
		tokenFill(tok, tokTypeNotEquals, tokValueTypeNone, NULL, 0);
		*s += 2;
		return 1;
	}

	return 0;
}

int matchPlus(token *tok, char **s)
{
	if (**s == '+')
	{
		tokenFill(tok, tokTypePlus, tokValueTypeNone, NULL, 0);
		++*s;
		return 1;
	}

	return 0;
}

int matchMinus(token *tok, char **s)
{
	if (**s == '-')
	{
		tokenFill(tok, tokTypeMinus, tokValueTypeNone, NULL, 0);
		++*s;
		return 1;
	}

	return 0;
}

int matchTimes(token *tok, char **s)
{
	if (**s == '*')
	{
		tokenFill(tok, tokTypeTimes, tokValueTypeNone, NULL, 0);
		++*s;
		return 1;
	}

	return 0;
}

int matchDividedBy(token *tok, char **s)
{
	if (**s == '/')
	{
		tokenFill(tok, tokTypeDividedBy, tokValueTypeNone, NULL, 0);
		++*s;
		return 1;
	}

	return 0;
}

int matchPoke(token *tok, char **s)
{
	if (!strncasecmp(*s, "poke", 4))
	{
		tokenFill(tok, tokTypeFunctionPeek, tokValueTypeNone, NULL, 0);
		*s += 4;
		return 1;
	}

	return 0;
}

