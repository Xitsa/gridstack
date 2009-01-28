/*
 * GridStack.lex
 */

%{
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "common.h"
#include "GridStack.tab.h"


#undef ECHO
#define ECHO
%}

digit             [0-9]

int_constant      {digit}+

%option noyywrap

%%
[Mm][Oo][Nn][Ii][Tt][Oo][Rr]            {
                                            yylval.IntVal=MONITOR;
                                            return MONITOR;
                                        }
[Hh][Ss][Tt][Aa][Cc][Kk]                {
                                            yylval.IntVal=HSTACK;
                                            return HSTACK;
                                        }
[Vv][Ss][Tt][Aa][Cc][Kk]                {
                                            yylval.IntVal=VSTACK;
                                            return VSTACK;
                                        }
[Ww][Ii][Nn][Dd][Oo][Ww]                {
                                            yylval.IntVal=WINDOW;
                                            return WINDOW;
                                        }
{int_constant}!                         {
                                            sscanf(yytext,"%d!",&yylval.IntVal);
                                            return FIX_DIMENTION;
                                        }
{int_constant}                          {
                                            sscanf(yytext,"%d",&yylval.IntVal);
                                            return DIMENSION;
                                        }
\(                                      {
                                            yylval.IntVal=OPEN;
                                            return OPEN;
                                        }
\)                                      {
                                            yylval.IntVal=CLOSE;
                                            return CLOSE;
                                        }
#.*$                                    /* Пропустим комментарии до конца строки */
[\n\r\t ]+                              /* Пробелы для нас ничего не значат */
.                                       {
                                            return *yytext;
                                        }
%%

/*
 * Открыть указанный файл для разбора
 */
void InitParse(char* FileName)
  {
    yyin=fopen(FileName,"rt");
  }//InitParse
////////////////////////////////////////////////////////////////////////////////
/*
 * Закрыть файл разбора
 */
void FinishParse(void)
  {
    fclose(yyin);
  }//FinishParse
////////////////////////////////////////////////////////////////////////////////
