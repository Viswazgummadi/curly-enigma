/**
 * @file main.c
 * @brief Main entry point for the compiler.
 * 
 * This file initializes necessary components, parses the input file,
 * builds an Abstract Syntax Tree (AST), performs semantic checks,
 * and generates assembly code.
 */

#include "compiler.h"

/** External declaration of Flex's input file handle */
extern FILE *yyin;

/** Function prototype for Bison's parser */
int yyparse();

/** Root node of the Abstract Syntax Tree (AST) */
ASTNode *root = NULL;

/** Debug flag for parser debugging (0 = off, 1 = on) */
extern int yydebug;

/** Global symbol table used for semantic analysis */
SymbolTable symTable;

/**
 * @brief Main function for the compiler.
 * 
 * This function handles command-line argument parsing, file handling,
 * and invokes various stages of the compiler, including parsing,
 * semantic analysis, and code generation.
 * 
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return int Returns 0 on success, 1 on failure.
 */
int main(int argc, char **argv) {
    // Ensure correct command-line usage
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Open the input file for reading
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("Error opening input file");
        return 1;
    }
    printf("Input file opened successfully\n");

    // Initialize the symbol table for semantic analysis
    initSymbolTable(&symTable);
    
    // Enable debugging output for the parser if needed
    yydebug = 1;
    
    // Start parsing
    printf("Parsing input file...\n");
    if (yyparse() != 0) {
        fprintf(stderr, "Parse failed\n");
        fclose(yyin);
        return 1;
    }

    // Ensure that an AST was generated
    if (root == NULL) {
        fprintf(stderr, "Error: AST root is NULL\n");
        fclose(yyin);
        return 1;
    }

    // Print the constructed AST
    printf("AST Structure:\n");
    printAST(root, 0);

    // Perform semantic analysis on the AST
    printf("Semantic Checking:\n");
    semanticCheck(root);

    // Generate assembly code from the AST
    printf("Code Generation:\n");
    printf("section .text\n");
    printf("global _start\n\n");
    printf("_start:\n");
    generateCode(root, stdout);
    
    // Append system exit code to the generated assembly
    printf(" mov ebx, eax\n"); // Move return value into ebx
    printf(" mov eax, 1\n");  // sys_exit system call
    printf(" int 0x80\n");    // Invoke system interrupt

    // Clean up and close input file
    fclose(yyin);
    freeAST(root);

    return 0;
}
