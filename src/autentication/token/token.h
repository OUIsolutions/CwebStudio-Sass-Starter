

typedef struct  Token{
    bool infinite;
    char *user_id;
    char *token;
}Token;

void Token_free(Token *self);


char *create_token_string(char *user_id, char *password, bool infinite);


Token * extract_token(char *token);

void Token_represent(Token *self);
