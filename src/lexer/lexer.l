%{
#include "compiler.h"
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#define SAVE_TOKEN yylval.stringValue = strdup(yytext)
#define SAVE_TOKEN do { \
    yylval.stringValue = strdup(yytext); \
    if (!yylval.stringValue) { \
        fprintf(stderr, "Error: strdup failed in lexer\n"); \
        exit(1); \
    } \
} while(0)
#define REPORT_ERROR printf("Lexing Error on line %d\n", yylineno)
int yywrap(void) {
    return 1;
}
%}

%%
[ \t\n]                 ;
[0-9]+                  { yylval.intValue = atoi(yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]*  { SAVE_TOKEN; return IDENTIFIER; }
"="                     { return ASSIGN; }
"+"                     { return PLUS; }
"-"                     { return MINUS; }
"*"                     { return MULTIPLY; }
"/"                     { return DIVIDE; }
"("                     { return LPAREN; }
")"                     { return RPAREN; }
";"                     { return SEMICOLON; }
.                       { REPORT_ERROR; }
%%
