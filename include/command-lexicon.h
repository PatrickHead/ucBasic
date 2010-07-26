/*
    command-lexicon.h
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

#ifndef COMMAND_LEXICON_H
#define COMMAND_LEXICON_H

int matchBye(token *tok, char **s);
int matchClear(token *tok, char **s);
int matchList(token *tok, char **s);
int matchRun(token *tok, char **s);
int matchSize(token *tok, char **s);
int matchFree(token *tok, char **s);

#endif // COMMAND_LEXICON_H
