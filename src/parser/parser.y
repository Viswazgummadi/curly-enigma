%{
#include "compiler.h"
#include <stdio.h>
#include <stdlib.h>



extern ASTNode *root;
int yylex();
void yyerror(const char *s);



#define YYDEBUG 1  // Enable Bison Debug Mode


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
        printf("Phase 1: Lexical Analysis Done :)\n"); // Message after lexical analysis is done
        root = $1;
    }
    ;

statement_list:
    statement                 {        printf("[DEBUG] Created NUMBER node: %p\n" , (void*)$1); $$ = $1; }
    | statement_list statement   {
                 printf("[DEBUG] Appending statement to list\n");
         $$ = createStatementListNode($1, $2);
    }
    ;

statement:
    IDENTIFIER ASSIGN expression SEMICOLON {         printf("[DEBUG] Assigning variable: %s\n", $1); $$ = createAssignNode($1, $3); free($1); }
    | expression SEMICOLON                {         printf("[DEBUG] Expression statement at %p\n", (void*)$1); $$ = $1; }
    ;

expression:
    NUMBER {
        printf("[DEBUG] Created NUMBER node: %d\n", $1);
        $$ = createNumNode($1);
    }
    | IDENTIFIER {
        printf("[DEBUG] Created VAR node: %s\n", $1);
        $$ = createVarNode(strdup($1));
        free($1);
    }
    | expression PLUS expression {
        printf("[DEBUG] Created OP_NODE: ADD\n");
        $$ = createOpNode(OP_ADD, $1, $3);
    }
    | expression MINUS expression {
        printf("[DEBUG] Created OP_NODE: SUB\n");
        $$ = createOpNode(OP_SUB, $1, $3);
    }
    | expression MULTIPLY expression {
        printf("[DEBUG] Created OP_NODE: MUL\n");
        $$ = createOpNode(OP_MUL, $1, $3);
    }
    | expression DIVIDE expression {
        printf("[DEBUG] Created OP_NODE: DIV\n");
        $$ = createOpNode(OP_DIV, $1, $3);
    }
    | LPAREN expression RPAREN {
        printf("[DEBUG] Parentheses Expression\n");
        $$ = $2;
    }
    ;
%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

