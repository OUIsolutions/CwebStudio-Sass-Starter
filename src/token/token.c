
void Token_free(Token *self){
    free(self->hash);
    free(self->user_id);
    free(self);
}

char * create_token_string(char *user_id, char *password){
    DtwHash * token_assignature = newDtwHash();
    dtw.hash.digest_string(token_assignature,user_id);
    dtw.hash.digest_string(token_assignature,password);
    dtw.hash.digest_long(token_assignature, time(NULL));

    CTextStack * token = newCTextStack_string_empty();

    stack.format(token,"%s",token_assignature->hash);
    stack.format(token,"%s",user_id);

    dtw.hash.free(token_assignature);
    return stack.self_transform_in_string_and_self_clear(token);
}


Token * extract_token(char *token){

    const int SHA_SIZE = 64;
    const int MAX_USER_SIZE = 30;
    const int MIN_USER_SIZE =1;

    CTextStack * element = newCTextStack_string(token);

    if(element->size <  SHA_SIZE + MIN_USER_SIZE){
        stack.free(element);
        return NULL;
    }
    if(element->size >  SHA_SIZE + MAX_USER_SIZE){
        stack.free(element);
        return NULL;
    }

    Token  *t = (Token*) malloc(sizeof (Token));
    t->hash = stack.self_transform_in_string_and_self_clear(
            stack.substr(element,0,SHA_SIZE)
    );

    t->user_id = stack.self_transform_in_string_and_self_clear(
            stack.substr(element,SHA_SIZE,-1)
    );
    stack.free(element);

    return t;





}