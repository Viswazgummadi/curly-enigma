#include "ast/ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler.h"
ASTNode* createNumNode(int num) {
    printf("Creating NUM_NODE with value: %d\n", num);
    ASTNode *node = malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Error: Failed to allocate memory for NUM_NODE\n");
        exit(1);
    }
    node->type = NUM_NODE;
    node->value = num;
    node->left = NULL;
    node->right = NULL;
    return node;
}

ASTNode* createVarNode(char *name) {
    printf("Creating VAR_NODE with name: %s\n", name ? name : "NULL");
    ASTNode *node = malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Error: Failed to allocate memory for VAR_NODE\n");
        exit(1);
    }
    node->type = VAR_NODE;
    node->varName = name ? strdup(name) : NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

ASTNode* createOpNode(NodeType op, ASTNode *left, ASTNode *right) {
    printf("Creating OP_NODE with type: %d\n", op);
    ASTNode *node = malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Error: Failed to allocate memory for OP_NODE\n");
        exit(1);
    }
    node->type = op;
    node->left = left;
    node->right = right;
    return node;
}

ASTNode* createAssignNode(char *name, ASTNode *expr) {
    printf("Creating ASSIGN_NODE for variable: %s\n", name ? name : "NULL");
    ASTNode *node = malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Error: Failed to allocate memory for ASSIGN_NODE\n");
        exit(1);
    }
    node->type = ASSIGN_NODE;
    node->varName = name ? strdup(name) : NULL;
    node->left = expr;
    node->right = NULL;
    return node;
}

void freeAST(ASTNode *node) {
    if (!node) return;

    switch (node->type) {
        case ASSIGN_NODE:
        case VAR_NODE:
            if (node->varName) {
                free(node->varName);
                node->varName = NULL; // Prevent double free
            }
            freeAST(node->left);
            break;
        case OP_ADD:
        case OP_SUB:
        case OP_MUL:
        case OP_DIV:
            freeAST(node->left);
            freeAST(node->right);
            break;
        case NUM_NODE:
            break;
        case STATEMENT_LIST:
            freeAST(node->left);
            freeAST(node->right);
            break;
        default:
            fprintf(stderr, "Error: Unknown node type in freeAST\n");
            }
    free(node);
}
// Function to print the AST (for debugging)
void printAST(ASTNode *node, int depth) {
    if (!node) return;

    for (int i = 0; i < depth; i++) {
        printf("  "); // Indentation for depth
    }

    switch (node->type) {
        case NUM_NODE:
            printf("NUM: %d\n", node->value);
            break;
        case VAR_NODE:
            printf("VAR: %s\n", node->varName ? node->varName : "NULL");
            break;

        case ASSIGN_NODE:
            printf("ASSIGN: %s =\n", node->varName);
            printAST(node->left, depth + 1);
            break;
        case OP_ADD:
            printf("ADD:\n");
            printAST(node->left, depth + 1);
            printAST(node->right, depth + 1);
            break;
        case OP_SUB:
            printf("SUB:\n");
            printAST(node->left, depth + 1);
            printAST(node->right, depth + 1);
            break;
        case OP_MUL:
            printf("MUL:\n");
            printAST(node->left, depth + 1);
            printAST(node->right, depth + 1);
            break;
        case OP_DIV:
            printf("DIV:\n");
            printAST(node->left, depth + 1);
            printAST(node->right, depth + 1);
            break;

        case STATEMENT_LIST:
            printf("STATEMENT_LIST:\n");
            printAST(node->left, depth + 1);
            printAST(node->right, depth + 1);
            break;

        default:
            printf("Unknown node type\n");
    }
}
ASTNode* createStatementListNode(ASTNode *left, ASTNode *right) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = STATEMENT_LIST;
    node->left = left;
    node->right = right;
    return node;
}
