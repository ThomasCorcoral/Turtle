/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_HOME_THOMAS_DOCUMENTS_ETUDES_L3_S6_AS_TURTLE_BUILD_TURTLE_PARSER_H_INCLUDED
# define YY_YY_HOME_THOMAS_DOCUMENTS_ETUDES_L3_S6_AS_TURTLE_BUILD_TURTLE_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    VALUE = 258,
    NAME = 259,
    KW_PRINT = 260,
    KW_FORWARD = 261,
    KW_FW = 262,
    KW_BACKWARD = 263,
    KW_BW = 264,
    KW_POSITION = 265,
    KW_POS = 266,
    KW_UP = 267,
    KW_DOWN = 268,
    KW_RIGHT = 269,
    KW_RT = 270,
    KW_LEFT = 271,
    KW_LT = 272,
    KW_HEADING = 273,
    KW_HD = 274,
    KW_COLOR = 275,
    KW_HOME = 276
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 18 "turtle-parser.y" /* yacc.c:1909  */

  double value;
  char *name;
  struct ast_node *node;

#line 82 "/home/thomas/Documents/Etudes/L3/S6/AS/Turtle/build/turtle-parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (struct ast *ret);

#endif /* !YY_YY_HOME_THOMAS_DOCUMENTS_ETUDES_L3_S6_AS_TURTLE_BUILD_TURTLE_PARSER_H_INCLUDED  */
