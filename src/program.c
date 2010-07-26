/*
    program.c
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

#include "variable.h"
#include "token.h"
#include "language-grammar.h"
#include "error.h"

#include "program.h"

static int _lineNumber = 0;
static char *_program = NULL;
static int _gosubStack[PROGRAM_SIZEOF_GOSUB_STACK];
static int _gosubStackIndex = -1;
static programMode _mode = progModeStored;

static int pushGosubCaller(int ln);
static int popGosubCaller(void);

char *programInit(void)
{
	static int firstTime = 1;

	if (firstTime)
	{
		_program = (char *)malloc(PROGRAM_SIZEOF_DATA_SPACE);
		if (!_program) return NULL;
		firstTime = 0;
	}

	memset(_program, 0, PROGRAM_SIZEOF_DATA_SPACE);

	programSetLineNumber(0);

	memset(_gosubStack, 0, sizeof(int) * PROGRAM_SIZEOF_GOSUB_STACK);
	_gosubStackIndex = -1;

	variableInit();

	programSetMode(progModeStored);

	return _program;
}

void programSetLineNumber(int ln)
{
	_lineNumber = ln;

	return;
}

int programGetLineNumber(void)
{
	return _lineNumber;
}

void programSetValue(unsigned int address, unsigned char value)
{
	_program[address % PROGRAM_SIZEOF_DATA_SPACE] = value;
}

int programGetValue(unsigned int address)
{
	return (int)_program[address % PROGRAM_SIZEOF_DATA_SPACE];
}

char *programGotoLineNumber(int ln)
{
	char *newLineLocation = NULL;

	newLineLocation = programFindLineNumber(ln);
	if (!newLineLocation) return NULL;

	programSetLineNumber(atoi(newLineLocation));

	return newLineLocation;
}

char *programFindLineNumber(int ln)
{
	char *t = _program;
	int tln;

	if (!t) return NULL;

	while (*t)
	{
		tln = atoi(t);
		if (tln == ln) return t;
		while (*t != '\n') ++t;
		++t;
	}

	return NULL;
}

char *programFindNextLineNumber(int ln)
{
	char *t = _program;
	int tln;

	if (!t) return NULL;

	while (*t)
	{
		tln = atoi(t);
		if (tln > ln) return t;
		while (*t != '\n') ++t;
		++t;
	}

	return t;
}

char *programGosub(int ln)
{
	char *loc;
	int tmpLN;

	tmpLN = programGetLineNumber();
	loc = programFindLineNumber(tmpLN);
	if (!loc) return NULL;

	while (*loc)
	{
		if (*loc == '\n')
		{
			++loc;
			break;
		}

		++loc;
	}

	if (*loc) tmpLN = atoi(loc);

	loc = programGotoLineNumber(ln);
	if (!loc) return NULL;

	if (pushGosubCaller(tmpLN)) return NULL;

	return loc;
}

char *programReturn(void)
{
	int tmpLN;
	char *loc;

	tmpLN = popGosubCaller();
	if (tmpLN < 0) return NULL;

	loc = programGotoLineNumber(tmpLN);

	return loc;
}

int programRun(int ln)
{
	char *lp = _program;
	token tok;

	if (ln) lp = programGotoLineNumber(ln);

	if (!lp)
	{
		errorSet(ERROR_UNKNOWN_LINE_NUMBER);
		return 0;
	}

	do
	{
		tokenClear(&tok);
		if (!parseLine(&tok, &lp)) return 0;
	} while (*lp);

	if (!*lp) return 1;

	return 0;
}

void programPoke(unsigned int address, unsigned char value)
{
	programSetValue(address, value);
}

char *programGetProgram(void)
{
	return _program;
}

static int pushGosubCaller(int ln)
{
	++_gosubStackIndex;
	if (_gosubStackIndex == PROGRAM_SIZEOF_GOSUB_STACK)
	{
		_gosubStackIndex = -1;
		return -1;
	}

	_gosubStack[_gosubStackIndex] = ln;

	return 0;
}

static int popGosubCaller(void)
{
	if (_gosubStackIndex < 0) return -1;

	--_gosubStackIndex;

	return _gosubStack[_gosubStackIndex + 1];
}

programMode programGetMode(void)
{
	return _mode;
}

void programSetMode(programMode mode)
{
	_mode = mode;

	return;
}

int programGetSize(void)
{
	return strlen(_program);
}

int programGetFree(void)
{
	int size = programGetSize();

	return (PROGRAM_SIZEOF_DATA_SPACE - size);
}
