/* A Bison parser, made by GNU Bison 2.1.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005 Free Software Foundation, Inc.

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

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     MONITOR = 258,
     WINDOW = 259,
     HSTACK = 260,
     VSTACK = 261,
     OPEN = 262,
     CLOSE = 263,
     DIMENSION = 264,
     FIX_DIMENTION = 265
   };
#endif
/* Tokens.  */
#define MONITOR 258
#define WINDOW 259
#define HSTACK 260
#define VSTACK 261
#define OPEN 262
#define CLOSE 263
#define DIMENSION 264
#define FIX_DIMENTION 265




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 7 "GridStack.y"
typedef union YYSTYPE {
  int       IntVal;
  TRegion*  Region;
  TListCage*RegionList;
  TMonitor* Monitor;
 } YYSTYPE;
/* Line 1447 of yacc.c.  */
#line 65 "GridStack.tab.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



