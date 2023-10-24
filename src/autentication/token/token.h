

typedef struct  Token{
    bool infinite;
    char *user_id;
    char *token_id;
    char *sha;
}Token;

void Token_free(Token *self);


char *create_token_string(const char *user_id,const char * token_id,  const  char *password, bool infinite);


Token * extract_token(const char *token);

void Token_represent(Token *self);
