/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 336,                 /* "invalid token"  */
    PR_ENTERO = 301,               /* PR_ENTERO  */
    PR_REAL = 302,                 /* PR_REAL  */
    PR_FUNCION = 303,              /* PR_FUNCION  */
    PR_PRINCIPAL = 304,            /* PR_PRINCIPAL  */
    PR_RETORNAR = 305,             /* PR_RETORNAR  */
    PR_SEGUN = 306,                /* PR_SEGUN  */
    PR_CASO = 307,                 /* PR_CASO  */
    PR_DEFECTO = 308,              /* PR_DEFECTO  */
    PR_MIENTRAS = 309,             /* PR_MIENTRAS  */
    PR_AENTERO = 310,              /* PR_AENTERO  */
    PR_AREAL = 311,                /* PR_AREAL  */
    PR_Y = 312,                    /* PR_Y  */
    PR_O = 313,                    /* PR_O  */
    PR_ESCRIBIR = 335,             /* PR_ESCRIBIR  */
    TK_ID = 314,                   /* TK_ID  */
    CTE_ENTERA = 315,              /* CTE_ENTERA  */
    CTE_REAL = 316,                /* CTE_REAL  */
    OP_ASIG = 317,                 /* OP_ASIG  */
    OP_SUMA = 318,                 /* OP_SUMA  */
    OP_RESTA = 319,                /* OP_RESTA  */
    OP_MULT = 320,                 /* OP_MULT  */
    OP_DIV = 321,                  /* OP_DIV  */
    OP_MENOR = 322,                /* OP_MENOR  */
    OP_MAYOR = 323,                /* OP_MAYOR  */
    OP_DISTINTO = 324,             /* OP_DISTINTO  */
    OP_MENOR_IGUAL = 325,          /* OP_MENOR_IGUAL  */
    OP_MAYOR_IGUAL = 326,          /* OP_MAYOR_IGUAL  */
    OP_IGUAL = 327,                /* OP_IGUAL  */
    DELIM_PAR_A = 328,             /* DELIM_PAR_A  */
    DELIM_PAR_C = 329,             /* DELIM_PAR_C  */
    DELIM_LLAVE_A = 330,           /* DELIM_LLAVE_A  */
    DELIM_LLAVE_C = 331,           /* DELIM_LLAVE_C  */
    DELIM_PUNTOCOMA = 332,         /* DELIM_PUNTOCOMA  */
    DELIM_DOSPUNTOS = 333,         /* DELIM_DOSPUNTOS  */
    DELIM_PUNTO = 334              /* DELIM_PUNTO  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 13 "parser.y"

    char cadena[64];
    int valor_entero;
    float valor_real;

#line 107 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
