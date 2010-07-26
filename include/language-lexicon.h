/*
    language-lexicon.h
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

#ifndef LANGUAGE_LEXICON_H
#define LANGUAGE_LEXICON_H

	/*
	 * Function prototypes
	 */

int matchComma(token *tok, char **s);
int matchEOL(token *tok, char **s);
int matchNumber(token *tok, char **s);
int matchWhiteSpace(token *tok, char **s);
int matchString(token *tok, char **s);
int matchCharacterString(token *tok, char **s);
int matchDoubleQuote(token *tok, char **s);
int matchPrint(token *tok, char **s);
int matchInput(token *tok, char **s);
int matchLet(token *tok, char **s);
int matchGoto(token *tok, char **s);
int matchGosub(token *tok, char **s);
int matchReturn(token *tok, char **s);
int matchIf(token *tok, char **s);
int matchThen(token *tok, char **s);
int matchRemark(token *tok, char **s);
int matchFunction(token *tok, char **s);
int matchFunctionCall(token *tok, char **s);
int matchFunctionPeek(token *tok, char **s);
int matchLeftParenthesis(token *tok, char **s);
int matchRightParenthesis(token *tok, char **s);
int matchSeparator(token *tok, char **s);
int matchVariable(token *tok, char **s);
int matchRelationalOperator(token *tok, char **s);
int matchLessThan(token *tok, char **s);
int matchGreaterThan(token *tok, char **s);
int matchEquals(token *tok, char **s);
int matchLessThanOrEquals(token *tok, char **s);
int matchGreaterThanOrEquals(token *tok, char **s);
int matchNotEquals(token *tok, char **s);
int matchWhiteSpace(token *tok, char **s);
int matchSemicolon(token *tok, char **s);
int matchColon(token *tok, char **s);
int matchPoke(token *tok, char **s);
int matchPlus(token *tok, char **s);
int matchMinus(token *tok, char **s);
int matchTimes(token *tok, char **s);
int matchDividedBy(token *tok, char **s);

#endif // LANGUAGE_LEXICON_H
