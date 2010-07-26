/*
    language-grammar.c
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
#include <stdio.h>
#include <string.h>

#include "token.h"
#include "program.h"
#include "variable.h"
#include "language-lexicon.h"
#include "language-grammar.h"
#include "function.h"
#include "utility.h"
#include "error.h"

static token testToken;

/*
 *  line ::= *NUMBER statement EOL
 */

int parseLine(token *tok, char **s)
{
	int currentLineNumber = 0;
	programMode mode = programGetMode();

	switch (mode)
	{
		case progModeStored:
			if (!matchNumber(tok, s))
			{
				errorSet(ERROR_MALFORMED_LINE);
				return 0;
			}

			currentLineNumber = tok->n;
			programSetLineNumber(currentLineNumber);

			if (!matchWhiteSpace(&testToken, s))
			{
				errorSet(ERROR_MISSING_WHITESPACE);
				return 0;
			}
			break;

		case progModeImmediate:
			break;
	}

	matchWhiteSpace(&testToken, s);

	if (parseStatement(tok, s))
	{
		matchWhiteSpace(&testToken, s);

		errorSet(ERROR_OK);

		if (currentLineNumber && (currentLineNumber != programGetLineNumber()))
			return 1;

		if (matchEOL(tok, s))
			return 1;
		else
		{
			errorSet(ERROR_MALFORMED_LINE);
			return 0;
		}
	}

	errorSet(ERROR_SYNTAX);
  return 0;
}

/*
 *  statement ::= PRINT printlist
 *                INPUT varlist
 *                LET *VAR *EQUALS expression
 *                GOTO expression
 *                GOSUB expression
 *                RETURN
 *                IF expression *RELOP expression THEN statement
 *                REM *COMMENTSTRING
 *                CLEAR
 *                RUN
 *                RUN exprlist
 *                LIST
 *                LIST exprlist
 *                POKE expression *COMMA expression
 */

int parseStatement(token *tok, char **s)
{
	char var = 0;
	int value = 0;
	char *newLocation = NULL;
	tokenType op;
	int shortCircuit = 0;

  if (matchPrint(tok, s))
	{
		if (matchWhiteSpace(&testToken, s))
		{
			if (parsePrintList(tok, s))
				return 1;
		}
		errorSet(ERROR_MISSING_WHITESPACE);
		return 0;
	}

  if (matchInput(tok, s))
	{
		if (matchWhiteSpace(&testToken, s))
		{
			if (parseVariableList(tok, s))
				return 1;
		}
		errorSet(ERROR_MISSING_WHITESPACE);
		return 0;
	}

  if (matchLet(tok, s))
	{
		if (matchWhiteSpace(&testToken, s))
		{
			if (matchVariable(tok, s))
			{
				var = tok->c;
				matchWhiteSpace(&testToken, s);
				if (matchEquals(tok, s))
				{
					matchWhiteSpace(&testToken, s);
					if (parseExpression(tok, s))
					{
						variableSet(var, tok->n);
						return 1;
					}
				}
			}
		}
		errorSet(ERROR_MISSING_WHITESPACE);
		return 0;
	}

  if (matchGoto(tok, s))
	{
		if (matchWhiteSpace(&testToken, s))
		{
			if (parseExpression(tok, s))
			{
				if (!(newLocation = programGotoLineNumber(tok->n)))
				{
					errorSet(ERROR_UNKNOWN_LINE_NUMBER);
					return 0;
				}
				*s = newLocation;
				return 1;
			}
		}
		errorSet(ERROR_MISSING_WHITESPACE);
		return 0;
	}

  if (matchGosub(tok, s))
	{
		if (matchWhiteSpace(&testToken, s))
		{
			if (parseExpression(tok, s))
			{
				if (!(newLocation = programGosub(tok->n)))
				{
					errorSet(ERROR_UNKNOWN_LINE_NUMBER);
					return 0;
				}
				*s = newLocation;
				return 1;
			}
		}
		errorSet(ERROR_MISSING_WHITESPACE);
		return 0;
	}

  if (matchReturn(tok, s))
	{
		if (!(newLocation = programReturn()))
		{
			errorSet(ERROR_UNKNOWN_LINE_NUMBER);
			return 0;
		}
		*s = newLocation;
    return 1;
	}

  if (matchIf(tok, s))
	{
		if (matchWhiteSpace(&testToken, s))
		{
			if (parseExpression(tok, s))
			{
				value = tok->n;

				matchWhiteSpace(&testToken, s);
				if (matchRelationalOperator(tok, s))
				{
					op = tok->type;

					matchWhiteSpace(&testToken, s);
					if (parseExpression(tok, s))
					{
						shortCircuit = 0;

						switch (op)
						{
							case tokTypeLessThan:
								if (value < tok->n) break;
								shortCircuit = 1;
								break;
							case tokTypeGreaterThan:
								if (value > tok->n) break;
								shortCircuit = 1;
								break;
							case tokTypeEquals:
								if (value == tok->n) break;
								shortCircuit = 1;
								break;
							case tokTypeLessThanOrEquals:
								if (value <= tok->n) break;
								shortCircuit = 1;
								break;
							case tokTypeGreaterThanOrEquals:
								if (value >= tok->n) break;
								shortCircuit = 1;
								break;
							case tokTypeNotEquals:
								if (value != tok->n) break;
								shortCircuit = 1;
								break;
							default:
								errorSet(ERROR_RELATIONAL_OPERATOR_ASSERTION_FAILURE);
								return 0;
						}

						if (shortCircuit)
						{
							matchString(tok, s);
							return 1;
						}

						matchWhiteSpace(&testToken, s);
						if (matchThen(tok, s))
						{
							matchWhiteSpace(&testToken, s);
							if (parseStatement(tok, s))
								return 1;
						}
					}
				}
			}
		}
		errorSet(ERROR_MISSING_WHITESPACE);
		return 0;
	}

  if (matchRemark(tok, s))
	{
		if (matchWhiteSpace(&testToken, s))
		{
			if (matchString(tok, s))
				return 1;
		}
		errorSet(ERROR_MISSING_WHITESPACE);
		return 0;
	}

  if (matchPoke(tok, s))
	{
		if (matchWhiteSpace(&testToken, s))
		{
			if (parseExpression(tok, s))
			{
				value = tok->n;

				matchWhiteSpace(&testToken, s);
				if (matchComma(tok, s))
				{
					matchWhiteSpace(&testToken, s);
					if (parseExpression(tok, s))
					{
						programPoke(value, (char)tok->n);
						return 1;
					}
				}
			}
		}
		errorSet(ERROR_MISSING_WHITESPACE);
		return 0;
	}

  return 0;
}

/*
 *  printlist ::= printitem
 *                printitem *COLON
 *                printitem *SEPARATOR printlist
 */

int parsePrintList(token *tok, char **s)
{
  if (parsePrintItem(tok, s))
  {
		matchWhiteSpace(&testToken, s);
    if (matchColon(tok, s))
		{
			fflush(stdout);
      return 1;
		}
    if (matchSeparator(tok, s))
		{
			matchWhiteSpace(&testToken, s);
      if (parsePrintList(tok, s))
        return 1;
		}
		putchar('\n');
		return 1;
  }
	return 0;
}

/*
 *  printitem ::= expression
 *                *DOUBLEQUOTE *CHARACTERSTRING *DOUBLEQUOTE
 */

int parsePrintItem(token *tok, char **s)
{
  if (parseExpression(tok, s))
	{
		fputs(itos(tok->n), stdout);
		return 1;
	}

  if (matchDoubleQuote(tok, s))
    if (matchCharacterString(tok, s))
		{
			fputs(tok->s, stdout);
      if (matchDoubleQuote(tok, s))
        return 1;
		}

  return 0;
}

/*
 *  varlist ::= *VAR
 *              *VAR *COMMA varlist
 */

int parseVariableList(token *tok, char **s)
{
	char var;
	int i;
	char input[11];
	int c;

  if (matchVariable(tok, s))
  {
		var = tok->c;

		memset(input, 0, 11);

			// Eat whitespace
		do
		{
			c = getchar();
		} while ((c == ' ') || (c == '\t'));

			// Get digits
		for (i = 0; i < 11; i++)
		{
			if ((c < '0') || (c > '9')) break;
			input[i] = (char)c;
			c = getchar();
		}

		ungetc(c, stdin);

		variableSet(var, atoi(input));

		matchWhiteSpace(&testToken, s);
    if (matchComma(tok, s))
		{
			matchWhiteSpace(&testToken, s);
      if (parseVariableList(tok, s))
        return 1;
		}

			// Drain remaining input

		while ((fgetc(stdin)) != '\n') ;

    return 1;
  }

  return 0;
}

/*
 *  exprlist ::= expression
 *               expression *COMMA exprlist
 */

int parseExpressionList(token *tok, char **s)
{
  if (parseExpression(tok, s))
  {
		matchWhiteSpace(&testToken, s);
    if (matchComma(tok, s))
		{
			matchWhiteSpace(&testToken, s);
      if (parseExpression(tok, s))
        return 1;
			return 0;
		}
    return 1;
  }

  return 0;
}

/*
 *  expression ::= unsignedexpr
 *                 *PLUS unsignedexpr
 *                 *MINUS unsignedexpr
 */

int parseExpression(token *tok, char **s)
{
  if (parseUnsignedExpression(tok, s))
    return 1;

  if (matchPlus(tok, s))
	{
		matchWhiteSpace(&testToken, s);
    if (parseUnsignedExpression(tok, s))
      return 1;
		errorSet(ERROR_INVALID_EXPRESSION);
		return 0;
	}

  if (matchMinus(tok, s))
	{
		matchWhiteSpace(&testToken, s);
    if (parseUnsignedExpression(tok, s))
		{
			tok->n *= -1;
      return 1;
		}
		errorSet(ERROR_INVALID_EXPRESSION);
		return 0;
	}

	errorSet(ERROR_INVALID_EXPRESSION);
  return 0;
}

/*
 *  unsignedexpr ::= term
 *                   term *PLUS unsignedexpr
 *                   term *MINUS unsignedexpr
 */

int parseUnsignedExpression(token *tok, char **s)
{
	int firstTerm = 0;

  if (parseTerm(tok, s))
  {
		firstTerm = tok->n;

		matchWhiteSpace(&testToken, s);
    if (matchPlus(tok, s))
		{
			matchWhiteSpace(&testToken, s);
      if (parseUnsignedExpression(tok, s))
			{
				tok->n = firstTerm + tok->n;
        return 1;
			}
			return 0;
		}
    if (matchMinus(tok, s))
		{
			matchWhiteSpace(&testToken, s);
      if (parseUnsignedExpression(tok, s))
			{
				tok->n = firstTerm - tok->n;
        return 1;
			}
			return 0;
		}
    return 1;
  }

  return 0;
}

/*
 *  term ::= factor
 *           factor *TIMES term
 *           factor *DIVIDEDBY term
 */

int parseTerm(token *tok, char **s)
{
	int firstFactor = 0;

  if (parseFactor(tok, s))
  {
		firstFactor = tok->n;

		matchWhiteSpace(&testToken, s);
    if (matchTimes(tok, s))
		{
			matchWhiteSpace(&testToken, s);
      if (parseTerm(tok, s))
			{
				tok->n = firstFactor * tok->n;
        return 1;
			}
			return 0;
		}
    if (matchDividedBy(tok, s))
		{
			matchWhiteSpace(&testToken, s);
      if (parseTerm(tok, s))
			{
				tok->n = firstFactor * tok->n;
        return 1;
			}
			return 0;
		}
    return 1;
  }

  return 0;
}

/*
 *  factor ::= *VAR
 *             *NUMBER
 *             *LEFTPAREN expression *RIGHTPAREN
 *             function
 */

int parseFactor(token *tok, char **s)
{
  if (parseFunction(tok, s))
		return 1;

  if (matchLeftParenthesis(tok, s))
	{
		matchWhiteSpace(&testToken, s);
    if (parseExpression(tok, s))
		{
			matchWhiteSpace(&testToken, s);
      if (matchRightParenthesis(tok, s))
        return 1;
			errorSet(ERROR_UNMATCHED_PARENTHESES);
		}
		return 0;
	}

  if (matchVariable(tok, s))
	{
		tok->valueType = tokValueTypeNumber;
		tok->n = variableGet(tok->c);
    return 1;
	}

  if (matchNumber(tok, s))
    return 1;

  return 0;
}

/*
 *  function ::= CALL *LEFTPAREN expression *RIGHTPAREN
 *                PEEK *LEFTPAREN expression *RIGHTPAREN
 */

int parseFunction(token *tok, char **s)
{
	tokenType func;
	int value;


  if (matchFunction(tok, s))
  {
    func = tok->type;

		matchWhiteSpace(&testToken, s);
    if (matchLeftParenthesis(tok, s))
		{
			matchWhiteSpace(&testToken, s);
			if (parseExpression(tok, s))
			{
				value = tok->n;

				matchWhiteSpace(&testToken, s);
				if (matchRightParenthesis(tok, s))
				{
					switch (func)
					{
						case tokTypeFunctionCall:
							break;
						case tokTypeFunctionPeek:
							tok->type = tokTypeNumber;
							tok->valueType = tokValueTypeNumber;
							tok->n = functionPeek(value);
							break;
						default:
							errorSet(ERROR_FUNCTION_ASSERTION_FAILURE);
							return 0;
					}
					return 1;
				}
			}
		}
  }

  return 0;
}


