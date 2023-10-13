
void Token_free(Token *self){
    free(self->hash);
    free(self->hash);
    free(self);
}

char * create_token(char *user_id, char *password){
    DtwHash * token_assignature = newDtwHash();
    dtw.hash.digest_string(token_assignature,user_id);
    dtw.hash.digest_string(token_assignature,password);
    dtw.hash.digest_long(token_assignature, time(NULL));

    CHash *token_obj = newCHashArray(
        hash.newString(user_id),
        hash.newString(token_assignature->hash)
    );

    char *token_json = hash.dump_to_json_string(token_obj);
    hash.free(token_obj);
    dtw.hash.free(token_assignature);
    return dtw_base64_encode((unsigned char *)user_id, (long)strlen(token_json));
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