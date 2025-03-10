#include "compiler.h"

extern FILE *yyin;
int yyparse();
ASTNode *root = NULL;
int yydebug = 0;
SymbolTable symTable;

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("Error opening input file");
        return 1;
    }

    printf("Input file opened successfully\n");

    initSymbolTable(&symTable);
    yydebug = 0; // Enable debug output

    printf("Parsing input file...\n");
    if (yyparse() != 0) {
        fprintf(stderr, "Parse failed\n");
        fclose(yyin);
        return 1;
    }

    if (root == NULL) {
        fprintf(stderr, "Error: AST root is NULL\n");
        fclose(yyin);
        return 1;
    }

    printf("AST Structure:\n");
    printAST(root, 0);

    printf("Semantic Checking:\n");
    semanticCheck(root);

    printf("Code Generation:\n");
    printf("section .text\n");
    printf("global _start\n\n");
    printf("_start:\n");
    generateCode(root, stdout);
    printf(" mov ebx, eax\n"); // Exit code
    printf(" mov eax, 1\n"); // sys_exit
    printf(" int 0x80\n");

    fclose(yyin);
    freeAST(root);

    return 0;
}

