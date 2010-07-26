/*
    error.h
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

#ifndef ERROR_H
#define ERROR_H

	/*
	 * Macros defining error codes
	 */

#define ERROR_OK																		00
#define ERROR_FUNCTION_ASSERTION_FAILURE						10
#define ERROR_RELATIONAL_OPERATOR_ASSERTION_FAILURE 11
#define ERROR_INVALID_EXPRESSION										20
#define ERROR_UNMATCHED_PARENTHESES									21
#define ERROR_MALFORMED_LINE												22
#define ERROR_MISSING_WHITESPACE										23
#define ERROR_MISSING_ASSIGNMENT										24
#define ERROR_MISSING_VARIABLE											25
#define ERROR_DIVIDE_BY_ZERO												28
#define ERROR_SYNTAX																29
#define ERROR_OUT_OF_MEMORY													30
#define ERROR_UNKNOWN_LINE_NUMBER										40

	/*
	 * Function prototypes
	 */

void errorSet(unsigned char code);
unsigned char errorGet(void);
 
#endif // ERROR_H
