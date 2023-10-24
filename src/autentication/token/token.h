

typedef struct  Token{
    bool infinite;
    CTextStack * token_string;
    CTextStack * user_id;
    CTextStack  *token_id;
    CTextStack  *sha;
}Token;

void Token_free(Token *self);


Token * newToken(const char *user_id,const char * token_id,  const  char *password, bool infinite);


Token * extract_token(const char *token);

void Token_represent(Token *self);
