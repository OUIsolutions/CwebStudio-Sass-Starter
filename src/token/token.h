

typedef struct  Token{
    bool infinite;
    char *user_id;
    char *hash;
    char *token;
}Token;

void Token_free(Token *self);


Token * newToken(char *user_id, char *password, bool infinite);


Token * extract_token(char *token);
