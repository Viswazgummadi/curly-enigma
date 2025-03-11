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
[0-9]+                  { yylval.intValue = atoi(yytext); printf("TOKEN: NUMBER (%s)\n", yytext);return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]*  { SAVE_TOKEN; printf("TOKEN: IDENTIFIER (%s)\n", yytext);return IDENTIFIER; }
"="                     { printf("TOKEN: IDENTIFIER (%s)\n", yytext);return ASSIGN; }
"+"                     { printf("TOKEN: PLUS (+)\n");return PLUS; }
"-"                     { printf("TOKEN: MINUS (-)\n");return MINUS; }
"*"                     { printf("TOKEN: MULTIPLY (*)\n");return MULTIPLY; }
"/"                     { printf("TOKEN: DIVIDE (/)\n");return DIVIDE; }
"("                     { printf("TOKEN: LPAREN (()\n");return LPAREN; }
")"                     { printf("TOKEN: RPAREN ())\n");return RPAREN; }
";"                     { printf("TOKEN: SEMICOLON (;)\n");return SEMICOLON; }
.                       { printf("Lexing Error: Unrecognized token '%s'\n",yytext);REPORT_ERROR; }
%%


