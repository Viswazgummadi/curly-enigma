%{
#include "compiler.h"
#include <stdio.h>
#include <stdlib.h>

extern ASTNode *root;
int yylex();
void yyerror(const char *s);

%}

%union {
    ASTNode *node;
    int intValue;
    char *stringValue;
}

%token <intValue> NUMBER
%token <stringValue> IDENTIFIER


//%token  NUMBER IDENTIFIER ASSIGN PLUS MINUS MULTIPLY DIVIDE LPAREN RPAREN SEMICOLON

%token ASSIGN PLUS MINUS MULTIPLY DIVIDE LPAREN RPAREN SEMICOLON


//%type  <s> IDENTIFIER
//%type  <numVal> NUMBER


%type <node> program statement_list statement expression



%left PLUS MINUS
%left MULTIPLY DIVIDE



%%

program:
    statement_list {
        root = $1;
    }
    ;

statement_list:
    statement                 { $$ = $1; }
    | statement_list statement   {
         /* Append the new statement to the list.  A more robust implementation
         would create a proper list structure. */
         $$ = createStatementListNode($1, $2); /* Dummy OP_ADD */
    }
    ;

statement:
    IDENTIFIER ASSIGN expression SEMICOLON { $$ = createAssignNode($1, $3); free($1); }
    | expression SEMICOLON                { $$ = $1; }
    ;

expression:
    NUMBER                  { $$ = createNumNode($1); }
    | IDENTIFIER            { $$ = createVarNode($1); }
    | expression PLUS expression    { $$ = createOpNode(OP_ADD, $1, $3); }
    | expression MINUS expression   { $$ = createOpNode(OP_SUB, $1, $3); }
    | expression MULTIPLY expression { $$ = createOpNode(OP_MUL, $1, $3); }
    | expression DIVIDE expression   { $$ = createOpNode(OP_DIV, $1, $3); }
    | LPAREN expression RPAREN      { $$ = $2; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

