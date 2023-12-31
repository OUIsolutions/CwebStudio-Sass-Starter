

typedef struct  Token{
    bool infinite;
    CTextStack * token_string;
    CTextStack * user_id;
    CTextStack  *token_id;
    CTextStack  *sha;
}Token;

void Token_free(Token *self);


Token * newToken(const char *user_id,const char * token_id,  const  char *password, bool infinite);

CTextStack *create_token_string(bool infinite,const char *user_id,const char *token_id,const char *sha);


CTextStack  * create_sub_token_string(Token *original, const char *seed);

CTextStack  * create_sub_token_string_from_token_string(const char *token_string, const char *seed);


Token * extract_token(const char *token);



void Token_represent(Token *self);
