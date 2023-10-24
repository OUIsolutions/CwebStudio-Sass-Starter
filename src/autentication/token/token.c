
void Token_free(Token *self){

    if(self->user_id){
        stack.free(self->user_id);
    }

    if(self->sha){
        stack.free(self->sha);
    }

    if(self->token_id){
        stack.free(self->token_id);
    }

    if(self->token_string){
        stack.free(self->token_string);
    }

    free(self);
}
CTextStack *create_token_string(bool infinite,const char *user_id,const char *token_id,const char *sha){
    CTextStack  *token_string = newCTextStack_string_empty();

    const char INFINITE = 'i';
    const char FINITE = 'f';

    if(infinite){
        stack.format(token_string, "%c", INFINITE);
    }

    if(!infinite){
        stack.format(token_string, "%c", FINITE);
    }

    stack.format(token_string, "%t", sha);
    stack.format(token_string, "%s", user_id);
    stack.format(token_string, "%s", token_id);
    return token_string;
}

Token * newToken(const char *user_id,const char * token_id,  const  char *password, bool infinite){

    Token  *token = (Token*) malloc(sizeof (Token));
    *token = (Token){0};

    //creating the assignature
    DtwHash * token_assignature = newDtwHash();
    dtw.hash.digest_string(token_assignature,user_id);
    dtw.hash.digest_string(token_assignature,password);
    dtw.hash.digest_long(token_assignature, time(NULL));

    token->sha = newCTextStack_string(token_assignature->hash);
    dtw.hash.free(token_assignature);

    stack.self_substr( token->sha ,0,SHA_SIZE);

    //creating the token string
    token->token_string = create_token_string(infinite,user_id,token_id,token->sha->rendered_text);
    token->infinite = infinite;


    return token;

}


Token * extract_token(const char *token_string){


    int expected_size = 1+ SHA_SIZE + (ID_SIZE *2);
    CTextStack * element = newCTextStack_string(token_string);

    if(element->size != expected_size){
        stack.free(element);
        return NULL;
    }

    Token  *token = (Token*) malloc(sizeof (Token));
    *token = (Token){0};

    const char INFINITE = 'i';
    const char FINITE = 'f';

    if(element->rendered_text[0] == INFINITE){
        token->infinite = true;
    }
    else if(element->rendered_text[0] == FINITE){
        token->infinite = false;
    }

    else{
        stack.free(element);
        Token_free(token);
        return NULL;
    }
    int point = 1;

    token->sha = stack.substr(element,point, point+SHA_SIZE);
    point+=SHA_SIZE;


    token->user_id =stack.substr(element,point,point+ID_SIZE);
    point+=ID_SIZE;

    token->token_id =stack.substr(element,point, -1);

    stack.free(element);

    return token;



}

void Token_represent(Token *self){
    if(!self){
        return;
    }

    if(self->token_string){
        printf("token_string: %s\n",self->token_string->rendered_text);
    }
    if(self->token_id){
        printf("token_id: %s\n",self->token_id->rendered_text);
    }
    if(self->user_id){
        printf("user id: %s\n",self->user_id->rendered_text);
    }

    if(self->sha){
        printf("sha:%s\n",self->sha->rendered_text);
    }
    if(self->infinite){
        printf("infinite:%s\n",self->infinite ? "true":"false");
    }
}