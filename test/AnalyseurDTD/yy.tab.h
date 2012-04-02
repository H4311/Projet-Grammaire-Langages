/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ELEMENT = 258,
     ATTLIST = 259,
     CLOSE = 260,
     OPENPAR = 261,
     CLOSEPAR = 262,
     COMMA = 263,
     PIPE = 264,
     FIXED = 265,
     EMPTY = 266,
     ANY = 267,
     PCDATA = 268,
     AST = 269,
     QMARK = 270,
     PLUS = 271,
     CDATA = 272,
     IDENT = 273,
     TOKENTYPE = 274,
     DECLARATION = 275,
     STRING = 276
   };
#endif
/* Tokens.  */
#define ELEMENT 258
#define ATTLIST 259
#define CLOSE 260
#define OPENPAR 261
#define CLOSEPAR 262
#define COMMA 263
#define PIPE 264
#define FIXED 265
#define EMPTY 266
#define ANY 267
#define PCDATA 268
#define AST 269
#define QMARK 270
#define PLUS 271
#define CDATA 272
#define IDENT 273
#define TOKENTYPE 274
#define DECLARATION 275
#define STRING 276




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 8 "dtd.y"
{ 
   char *s; 
   }
/* Line 1529 of yacc.c.  */
#line 95 "yy.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

