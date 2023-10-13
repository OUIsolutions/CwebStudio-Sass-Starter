

typedef struct  Token{
    char *user_id;
    char *hash;
}Token;

void Token_free(Token *self);


char * create_token(char *user_id, char *password);


Token * extract_token(char *token);
