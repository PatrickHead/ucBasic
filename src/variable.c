/*
    variable.c
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

#include <string.h>

#include "variable.h"

static int _variables[26];

static char variableNameToIndex(char v);

void variableInit(void)
{
	memset(_variables, 0, sizeof(int) * VARIABLE_SIZEOF_VARIABLE_ARRAY);

	return;
}

void variableSet(char v, int n)
{
	v = variableNameToIndex(v);
	if (v < 0) return;

	_variables[(int)v] = n;

	return;
}

int variableGet(char v)
{
	v = variableNameToIndex(v);
	if (v < 0) return -1;

	return _variables[(int)v];
}

static char variableNameToIndex(char v)
{
	if ((v >= 'a') && (v <= 'z')) v -= 32;
	if ((v >= 'A') && (v <= 'Z')) v -= 'A';

	if ((v < 0) || (v > 26)) return -1;

	return v;
}

