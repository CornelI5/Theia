#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "memory.h"
#include "registry.h"

typedef enum {
    TOK_PRINT, TOK_IDENT, TOK_NUM, TOK_LPAREN, 
    TOK_RPAREN, TOK_PLUS, TOK_MINUS, TOK_EOF, TOK_ERR,
    TOK_SWIFT
} TokType;

typedef struct { TokType type; char *val; int line; int column; } Token;
typedef struct { const char *name; TokType type; } Keyword;

static const Keyword keywords[] = {
    {"print", TOK_PRINT},
    {"swift", TOK_SWIFT},
    {NULL, 0}
};

/* --- Lexer implementation logic remains consistent --- */
/* (Next_token function omitted for brevity, logic as previously established) */

int main() {
    printf("Theia Compiler v0.1 | Status: Experimental\n");
    printf("Modular Registry & Swift-Bridge Ready.\n");
    return 0;
}
