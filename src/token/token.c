
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

    int extra_size = ID_SIZE - strlen(user_id);
    CTextStack * token = newCTextStack_string_empty();
    for(int i =0; i < extra_size; i++){
        stack.format(token,"%c",'0');
    }
    stack.format(token,"%s",user_id);
    stack.format(token,"%s",token_assignature->hash);
    dtw.hash.free(token_assignature);
    return stack.self_transform_in_string_and_self_clear(token);
}


Token * extract_token(char *token){

    long size;
    char * json_string = (char*)dtw_base64_decode(token,&size);
    if(!json_string){
        return  NULL;
    }
    CHash * result = hash.load_from_json_strimg(json_string);
    free(json_string);
    char *user = array.getString(result,0);
    char *sha = array.getString(result,1);
    CHash_protected(result){
        Token  *self = (Token*) malloc(sizeof(Token));
        self->user_id = strdup(user);
        self->hash = strdup(sha);
        hash.free(result);
        return self;
    }

    hash.free(result);
    return NULL;


}