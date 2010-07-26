/*
    token.h
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

#ifndef TOKEN_H
#define TOKEN_H

typedef enum
{
		// Common tokens

	tokTypeComma,
	tokTypeNumber,
	tokTypeEOL,

		// Language specific tokens

	tokTypeCharacterString,
	tokTypeColon,
	tokTypeDividedBy,
	tokTypeEquals,
	tokTypeFree,
	tokTypeFunctionCall,
	tokTypeFunctionPeek,
	tokTypeGosub,
	tokTypeGoto,
	tokTypeGreaterThan,
	tokTypeGreaterThanOrEquals,
	tokTypeIf,
	tokTypeInput,
	tokTypeLeftParenthesis,
	tokTypeLessThan,
	tokTypeLessThanOrEquals,
	tokTypeLet,
	tokTypeMinus,
	tokTypeNotEquals,
	tokTypePlus,
	tokTypePoke,
	tokTypePrint,
	tokTypeRemark,
	tokTypeReturn,
	tokTypeRightParenthesis,
	tokTypeSemicolon,
	tokTypeSize,
	tokTypeString,
	tokTypeDoubleQuote,
	tokTypeThen,
	tokTypeTimes,
	tokTypeVariable,
	tokTypeWhiteSpace,

		// Command specific tokens

	tokTypeClear,
	tokTypeRun,
	tokTypeList

} tokenType;

typedef enum
{
	tokValueTypeNone,
	tokValueTypeString,
	tokValueTypeCharacter,
	tokValueTypeNumber
} tokenValueType;

typedef struct token
{
	tokenType type;
	tokenValueType valueType;
	union
	{
		char *s;
		char c;
		int n;
	};
} token;

void tokenFill(token *tok,
							 tokenType type,
							 tokenValueType valueType,
							 char *value,
							 int valueLength);

void tokenClear(token *tok);

#endif // TOKEN_H
