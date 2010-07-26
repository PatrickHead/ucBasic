/*
    variable.h
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

#ifndef VARIABLE_H
#define VARIABLE_H

	/*
	 * Macro defining total number of variables in language
	 *
	 * NOTE:  This can be adjusted downward, but would require an adjustment
	 *        to the range checking in variable.c and in the matchVariable()
	 *        function in language-lexicon.c
	 */

#define VARIABLE_SIZEOF_VARIABLE_ARRAY 26

	/*
	 * Function prototypes
	 */

void variableInit(void);
void variableSet(char v, int n);
int variableGet(char v);

#endif // VARIABLE_H
