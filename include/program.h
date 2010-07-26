/*
    program.h
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

#ifndef PROGRAM_H
#define PROGRAM_H

	/*
	 * Macros defining global memory for program and gosub stack space
	 *
	 * NOTE:  This will need to be adjusted for each implementation
	 * NOTE:  This should probably be autoconfigured somehow or a command line
	 *        macro
	 */

#define PROGRAM_SIZEOF_DATA_SPACE	2048
#define PROGRAM_SIZEOF_GOSUB_STACK 10

	/*
	 * Enumeration definining allowable values for programMode type
	 */

typedef enum
{
	progModeImmediate,
	progModeStored
} programMode;

	/*
	 * Function prototypes
	 */

char *programFindNextLineNumber(int ln);
char *programFindLineNumber(int ln);
int programGetLineNumber(void);
int programGetValue(unsigned int address);
char *programGetProgram(void);
char *programGosub(int ln);
char *programGotoLineNumber(int ln);
char *programInit(void);
void programPoke(unsigned int address, unsigned char value);
char *programReturn(void);
int programRun(int ln);
void programSetLineNumber(int ln);
void programSetValue(unsigned int address, unsigned char value);
programMode programGetMode(void);
void programSetMode(programMode mode);
int programGetSize(void);
int programGetFree(void);

#endif // PROGRAM_H
