#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "memory.h"

typedef enum {
    TOK_PRINT, TOK_IDENT, TOK_NUM, TOK_LPAREN, 
    TOK_RPAREN, TOK_PLUS, TOK_MINUS, TOK_EOF, TOK_ERR
} TokType;

typedef enum { LEX_OK, LEX_OUT_OF_MEMORY, LEX_INVALID_TOKEN } LexResult;

typedef struct { TokType type; char *val; int line; int column; } Token;

typedef struct { const char *name; TokType type; } Keyword;

static const Keyword keywords[] = { {"print", TOK_PRINT}, {NULL, 0} };

const char *token_name(TokType t) {
    switch (t) {
        case TOK_PRINT: return "PRINT";
        case TOK_IDENT: return "IDENT";
        case TOK_NUM:   return "NUMBER";
        case TOK_LPAREN: return "LPAREN";
        case TOK_RPAREN: return "RPAREN";
        case TOK_PLUS:   return "PLUS";
        case TOK_MINUS:  return "MINUS";
        case TOK_EOF:    return "EOF";
        default:         return "ERROR";
    }
}

LexResult next_token(const char **src, int *line, int *column, Token *out_token) {
    out_token->val = NULL;
    while (**src) {
        if (**src == '\n') { (*line)++; *column = 1; (*src)++; continue; }
        if (isspace((unsigned char)**src)) { (*column)++; (*src)++; continue; }
        break;
    }
    const char *start = *src;
    int start_col = *column;

    if (**src == '\0') {
        char *val = (char*)SAFE_MALLOC(1);
        *val = '\0';
        *out_token = (Token){TOK_EOF, val, *line, *column};
        return LEX_OK;
    }

    if (isalpha((unsigned char)**src) || **src == '_') {
        while (isalnum((unsigned char)**src) || **src == '_') { (*src)++; (*column)++; }
        size_t len = *src - start;
        char *val = (char*)SAFE_MALLOC(len + 1);
        memcpy(val, start, len); val[len] = '\0';
        TokType type = TOK_IDENT;
        for (const Keyword *k = keywords; k->name != NULL; k++) {
            if (strcmp(val, k->name) == 0) { type = k->type; break; }
        }
        *out_token = (Token){type, val, *line, start_col};
        return LEX_OK;
    }

    if (isdigit((unsigned char)**src)) {
        while (isdigit((unsigned char)**src)) { (*src)++; (*column)++; }
        size_t len = *src - start;
        char *val = (char*)SAFE_MALLOC(len + 1);
        memcpy(val, start, len); val[len] = '\0';
        *out_token = (Token){TOK_NUM, val, *line, start_col};
        return LEX_OK;
    }

    char c = *((*src)++); (*column)++;
    char *val = (char*)SAFE_MALLOC(2);
    val[0] = c; val[1] = '\0';
    TokType type = (c == '(') ? TOK_LPAREN : (c == ')') ? TOK_RPAREN : 
                   (c == '+') ? TOK_PLUS : (c == '-') ? TOK_MINUS : TOK_ERR;
    *out_token = (Token){type, val, *line, start_col};
    return (type == TOK_ERR) ? LEX_INVALID_TOKEN : LEX_OK;
}

int main() {
    const char *script = "print(123) + pizza";
    const char *p = script;
    int line = 1, column = 1;
    while (1) {
        Token t;
        LexResult res = next_token(&p, &line, &column, &t);
        if (res != LEX_OK) {
            fprintf(stderr, "Lexer Error at %d:%d\n", line, column);
            if (t.val) free(t.val);
            break;
        }
        printf("%-10s | %-10s | line %d col %d\n", token_name(t.type), t.val, t.line, t.column);
        free(t.val);
        if (t.type == TOK_EOF) break;
    }
    return 0;
}
