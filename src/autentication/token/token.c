
void Token_free(Token *self){

    if(self->user_id){
        free(self->user_id);
    }
    if(self->token){
        free(self->token);
    }

    free(self);
}

char * create_token_string(char *user_id, char *password, bool infinite){
    DtwHash * token_assignature = newDtwHash();
    dtw.hash.digest_string(token_assignature,user_id);
    dtw.hash.digest_string(token_assignature,password);
    dtw.hash.digest_long(token_assignature, time(NULL));
    CTextStack *token = newCTextStack_string_empty();
    if(infinite){
        stack.format(token,"i");
    }

    if(!infinite){
        stack.format(token,"f");
    }
    CTextStack * token_assignature_string = newCTextStack_string(token_assignature->hash);
    stack.self_substr(token_assignature_string,0,SHA_SIZE);
    stack.format(token,"%tc",token_assignature_string);
    stack.format(token,"%s",user_id);

    dtw.hash.free(token_assignature);

    return stack.self_transform_in_string_and_self_clear(token);

}


Token * extract_token(char *token_string){

    const int MAX_USER_SIZE = 30;
    const int MIN_USER_SIZE =1;
    int min_size = SHA_SIZE  + MIN_USER_SIZE + 1;

    CTextStack * element = newCTextStack_string(token_string);

    if(element->size <  min_size){
        stack.free(element);
        return NULL;
    }
    if(element->size >  SHA_SIZE + MAX_USER_SIZE +1){
        stack.free(element);
        return NULL;
    }


    Token  *token = (Token*) malloc(sizeof (Token));
    *token = (Token){0};
    token->token = strdup(token_string);

    if(element->rendered_text[0] == 'i'){
        token->infinite = true;
    }
    else if(element->rendered_text[0] == 'f'){
        token->infinite = false;
    }
    else{
        Token_free(token);
        return NULL;
    }

    token->user_id = stack.self_transform_in_string_and_self_clear(
            stack.substr(element,SHA_SIZE+1,-1)
    );

    stack.free(element);

    return token;



}

void Token_represent(Token *self){
    if(!self){
        return;
    }
    if(self->user_id){
        printf("user id: %s\n",self->user_id);
    }
    if(self->token){
        printf("token:%s\n",self->token);
    }
    if(self->infinite){
        printf("infinite:%s\n",self->infinite ? "true":"false");
    }
}