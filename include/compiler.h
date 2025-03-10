#ifndef COMPILER_H
#define COMPILER_H

// Include necessary standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Include other headers
#include "ast/ast.h"
#include "symbol/symbol.h"

// Define any global constants or configurations
#define MAX_SYMBOLS 100

// Declare external variables, if needed
extern FILE *yyin;
extern int yyparse();
extern ASTNode *root;
extern int yydebug;
extern SymbolTable symTable;

// Function prototypes (if needed)
void printAST(ASTNode *node, int depth);
void semanticCheck(ASTNode *node);
void generateCode(ASTNode *node, FILE *out);

#endif
