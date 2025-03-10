#ifndef AST_H
#define AST_H

typedef enum {
    OP_ADD, OP_SUB, OP_MUL, OP_DIV,
    NUM_NODE, VAR_NODE, ASSIGN_NODE,
    STATEMENT_LIST  // Add this line
} NodeType;

typedef struct ASTNode {
    NodeType type;
    union {
        int value;              // For NUM_NODE
        char *varName;           // For VAR_NODE/ASSIGN_NODE
        struct {                // For operators
            struct ASTNode *left;
            struct ASTNode *right;
        };
    };
} ASTNode;

ASTNode* createNumNode(int num);
ASTNode* createVarNode(char *name);
ASTNode* createOpNode(NodeType op, ASTNode *left, ASTNode *right);
ASTNode* createAssignNode(char *name, ASTNode *expr);
void freeAST(ASTNode *node);
void printAST(ASTNode *node, int depth);
ASTNode* createStatementListNode(ASTNode *left, ASTNode *right);

#endif
