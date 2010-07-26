/*
    ub.c
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
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "program.h"
#include "token.h"
#include "command-grammar.h"
#include "error.h"

int loadProgram(char *dataSpace, char *name);
int commandLine(char *p);
char *tbError(unsigned char code);

int main(int argc, char **argv)
{
	char *program;

	program = programInit();
	if (!program) return -1;

	if (argc > 1) if (loadProgram(program, argv[1])) return -1;

	commandLine(program);

	return 0;
}

int commandLine(char *p)
{
	char line[81];
	char *lp;
	token tok;

	programSetLineNumber(0);

	for (;;)
	{
		lp = line;
		memset(line, 0, 81);
		fputs("> ", stdout);
		fflush(stdin);
		fgets(line, 80, stdin);
		if ((strlen(line) > 1) && !parseCommand(&tok, &lp))
		{
			fputs("Error: ", stdout);
			fputs(tbError(errorGet()), stdout);
			putchar('\n');
		}
		errorSet(ERROR_OK);
/*
		else if (!strncasecmp(line, "load ", 5))
		{
			line[strlen(line) -1] = 0;
			loadProgram(p, &line[5]);
		}
*/
	}

	return 1;
}

int loadProgram(char *dataSpace, char *name)
{
	FILE *f;
	struct stat st;
	char *t;

	if (stat(name, &st))
		return -1;

	if (st.st_size >= PROGRAM_SIZEOF_DATA_SPACE) return -1;

	f = fopen(name, "r");
	if (!f) return -1;

	for (t = dataSpace; !feof(f); ++t)
		*t = fgetc(f);

	*(t-1) = 0;

	fclose(f);

	return 0;
}

char *tbError(unsigned char code)
{
	switch (code)
	{
		case ERROR_OK:
			return "(00) OK";
		case ERROR_FUNCTION_ASSERTION_FAILURE:
			return "(10) FUNCTION ASSERTION FAILURE";
		case ERROR_RELATIONAL_OPERATOR_ASSERTION_FAILURE:
			return "(11) RELATIONAL OPERATOR ASSERTION FAILURE";
		case ERROR_INVALID_EXPRESSION:
			return "(20) INVALID EXPRESSION";
		case ERROR_UNMATCHED_PARENTHESES:
			return "(21) UNMATCHED PARENTHESES";
		case ERROR_MALFORMED_LINE:
			return "(22) MALFORMED LINE";
		case ERROR_MISSING_WHITESPACE:
			return "(23) MISSING WHITESPACE";
		case ERROR_DIVIDE_BY_ZERO:
			return "(24) DIVIDE BY ZERO";
		case ERROR_SYNTAX:
			return "(29) SYNTAX";
		case ERROR_OUT_OF_MEMORY:
			return "(30) OUT OF MEMORY";
		case ERROR_UNKNOWN_LINE_NUMBER:
			return "(40) UNKNOWN LINE NUMBER";
		default:
			return "(\?\?) UNKNOWN CODE";
	}

	return "error";
}

