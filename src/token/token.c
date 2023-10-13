
void Token_free(Token *self){
    free(self->hash);
    free(self->hash);
    free(self);
}

char * create_token_string(char *user_id, char *password){
    DtwHash * token_assignature = newDtwHash();
    dtw.hash.digest_string(token_assignature,user_id);
    dtw.hash.digest_string(token_assignature,password);
    dtw.hash.digest_long(token_assignature, time(NULL));

    CTextStack * token = newCTextStack_string_empty();
    int user_size = (int)strlen(user_id);

    if(user_size >= 10){
        stack.format(token,"%d", user_size);
    }
    else{
        stack.format(token,"0%d", user_size);
    }

    stack.format(token,"%s",user_id);
    stack.format(token,"%s",token_assignature->hash);
    dtw.hash.free(token_assignature);
    return stack.self_transform_in_string_and_self_clear(token);
}


Token * extract_token(char *token){

    CTextStack * element = newCTextStack_string(token);
    long first_num = stack.parse_to_integer(element);
    if(first_num == -1){
        stack.free(element);
        return NULL;
    }
    printf("%ld",first_num);
    stack.free(element);

    return NULL;


}