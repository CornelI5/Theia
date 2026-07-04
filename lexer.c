#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    TOKEN_PRINT,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_EOF,
    TOKEN_UNKNOWN
} TokenType;

const char* token_type_to_str(TokenType type) {
    switch (type) {
        case TOKEN_PRINT: return "PRINT";
        case TOKEN_LPAREN: return "LPAREN";
        case TOKEN_RPAREN: return "RPAREN";
        case TOKEN_EOF: return "EOF";
        default: return "UNKNOWN";
    }
}

void lex(const char* input) {
    int i = 0;
    int len = strlen(input);

    while (i < len) {
        if (isspace(input[i])) {
            i++;
            continue;
        }

        if (strncmp(&input[i], "print", 5) == 0) {
            printf("Token: %s\n", token_type_to_str(TOKEN_PRINT));
            i += 5;
        } else if (input[i] == '(') {
            printf("Token: %s\n", token_type_to_str(TOKEN_LPAREN));
            i++;
        } else if (input[i] == ')') {
            printf("Token: %s\n", token_type_to_str(TOKEN_RPAREN));
            i++;
        } else {
            printf("Token: UNKNOWN (char: %c)\n", input[i]);
            i++;
        }
    }
    printf("Token: %s\n", token_type_to_str(TOKEN_EOF));
}

int main() {
    const char* source = "print ()";
    
    printf("Lexing: %s\n", source);
    lex(source);
    
    return 0;
}
