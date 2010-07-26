/*
    language-grammar.h
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

#ifndef LANGUAGE_GRAMMAR_H
#define LANGUAGE_GRAMMER_H

int parseLine(token *tok, char **s);
int parseStatement(token *tok, char **s);
int parsePrintList(token *tok, char **s);
int parsePrintItem(token *tok, char **s);
int parseVariableList(token *tok, char **s);
int parseExpressionList(token *tok, char **s);
int parseExpression(token *tok, char **s);
int parseUnsignedExpression(token *tok, char **s);
int parseTerm(token *tok, char **s);
int parseFactor(token *tok, char **s);
int parseFunction(token *tok, char **s);

#endif // LANGUAGE_GRAMMAR_H
