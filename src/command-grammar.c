/*
    command-grammar.c
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
#include "command-lexicon.h"
#include "language-lexicon.h"
#include "language-grammar.h"
#include "error.h"
#include "utility.h"

#include "command-grammar.h"

static token testToken;

static int deleteLine(int line);
static int insertLine(int line, char *text);

/*
 *  command ::= CLEAR
 *  						run
 *  						list
 */

int parseCommand(token *tok, char **s)
{
	int line;
	int r;

	if (matchNumber(tok, s))
	{
		line = tok->n;
		if (!matchWhiteSpace(tok, s)) // delete line
			return deleteLine(line);
		else	// add line
		{
			matchString(tok, s);
			return insertLine(line, tok->s);
		}
	}

	if (matchSize(tok, s))
	{
		puts(itos(programGetSize()));
		return 1;
	}

	if (matchFree(tok, s))
	{
		puts(itos(programGetFree()));
		return 1;
	}

  if (matchClear(tok, s))
	{
		programInit();
		return 1;
	}

	if (matchBye(tok, s))
	{
		exit(0);
	}

	if (parseRun(tok, s))
		return 1;
	else if (errorGet() != ERROR_OK) return 0;

	if (parseList(tok, s))
		return 1;
	else if (errorGet() != ERROR_OK) return 0;

	programSetMode(progModeImmediate);
	r = parseLine(tok, s);
	programSetMode(progModeStored);

	return r;
}

/*
 *  run ::= RUN
 *  				RUN *LINENUMBER
 */

int parseRun(token *tok, char **s)
{
	int line = 0;

	if (matchRun(tok, s))
	{
		if (matchWhiteSpace(tok, s))
		{
			if (matchNumber(tok, s))
				line = tok->n;
			else
				return 0;
		}

		return programRun(line);
	}

  return 0;
}

/*
 *  list ::= LIST
 *  				 LIST *LINENUMBER
 *  				 LIST *LINENUMBER *COMMA *LINENUMBER
 */

int parseList(token *tok, char **s)
{
	int firstLine, lastLine;
	int line;
	int print = 0;
	char *prog;

	firstLine = lastLine = 0;

	if (matchList(tok, s))
	{
		matchWhiteSpace(tok, s);
		if (matchNumber(tok, s))
		{
			firstLine = lastLine = tok->n;

			matchWhiteSpace(tok, s);
			if (matchComma(&testToken, s))
			{
				matchWhiteSpace(tok, s);
				if (matchNumber(tok, s))
					lastLine = tok->n;
				else return 0;
			}
		}

		prog = programGetProgram();
		if (!prog)
		{
			errorSet(ERROR_OUT_OF_MEMORY);
			return 0;
		}

		while (*prog)
		{
			line = atoi(prog);

			if (lastLine && (line > lastLine)) break;

			if (line >= firstLine) print = 1;

			do
			{
				if (print) putchar(*prog);
				++prog;
			} while (*prog != '\n');
			if (print) putchar(*prog);

			++prog;
		}

		return 1;
	}

	return 0;
}

static int deleteLine(int line)
{
	char *this, *next;
	char *prog;
	int size;

	prog = programGetProgram();
	if (!prog)
	{
		errorSet(ERROR_OUT_OF_MEMORY);
		return 0;
	}

	this = programFindLineNumber(line);
	if (!this)
	{
		errorSet(ERROR_UNKNOWN_LINE_NUMBER);
		return 0;
	}

		// Scan to the next line

	for (next = this; *next != '\n'; next++) ;
	++next;

		// Shuffle the program up, overwriting this line

	while (*next)
	{
		*this = *next;
		++this;
		++next;
	}
	*this = 0;

	size = programGetSize();

	memset(this, 0, PROGRAM_SIZEOF_DATA_SPACE - size);

	return 1;
}

static int insertLine(int line, char *text)
{
	char *lineStr;
	int lineLen = 0;
	int i;
	char *insertPoint = NULL;
	char *end = NULL;
	char *newEnd = NULL;
	char *prog = NULL;

	prog = programGetProgram();
	if (!prog)
	{
		errorSet(ERROR_OUT_OF_MEMORY);
		return 0;
	}

	deleteLine(line);
	errorSet(ERROR_OK);

	lineStr = itos(line);

	lineLen = strlen(text) + strlen(lineStr) + 2; // add 1 for space and 1 for NL

		// Find insertion point

	insertPoint = programFindNextLineNumber(line);
	if (!insertPoint)
	{
		errorSet(ERROR_OUT_OF_MEMORY);
		return 0;
	}

		// Find end of current program

	end = prog + strlen(prog) - 1;

		// Calculate proposed end of edited program

	newEnd = end + lineLen;
	if ((newEnd - prog) > PROGRAM_SIZEOF_DATA_SPACE)
	{
		errorSet(ERROR_OUT_OF_MEMORY);
		return 0;
	}

		// Shuffle rest of program down, must be backwards

	for (; end >= insertPoint; --end, --newEnd)
		*newEnd = *end;

		// Copy in this line

	for (i = 0; i < strlen(lineStr); i++)
		insertPoint[i] = lineStr[i];

	insertPoint[i] = ' ';

	insertPoint += i + 1;

	for (i = 0; i < strlen(text); i++)
		insertPoint[i] = text[i];

	insertPoint[i] = '\n';

	return 1;
}

