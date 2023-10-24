

DtwResource *get_all_tokens_rource(DtwResource *user,Token *token){
    if(token->infinite){
        //data/elements/{user}/infinite_token/
        return resource.sub_resource(user, INFINITE_TOKENS_PATH);

    }
    if(token->infinite == false){
        //data/elements/{user}/infinite_token/
        return resource.sub_resource(user, FINITE_TOKENS_PATH);
    }
}

DtwResource *get_token_resource(DtwResource *user,Token *token){

    DtwResource  *all_tokens = get_all_tokens_rource(user,token);
    if(resource.type(all_tokens) == DTW_NOT_FOUND){
        return NULL;
    }

    DtwResource *current = resource.sub_resource(all_tokens,"%s",token->token_id->rendered_text);
    if(resource.type(current) == DTW_NOT_FOUND){
        return NULL;
    }
    return  current;

}
Token * database_create_finite_token(DtwResource *user, const char *password, bool allow_renew, int expiration){

    //data/elements/{user}/finite_tokens/
    DtwResource  *all_tokens = resource.sub_resource(user, FINITE_TOKENS_PATH);
    //data/elements/{user}/finite_tokens/{id}/
    DtwResource  *token_resource = resource.sub_resource_random(all_tokens,NULL);


    //data/elements/{user}/finite_tokens/{id}/sha
    DtwResource *sha_resurce = resource.sub_resource(token_resource, SHA_PATH);
    Token *token = newToken(user->name,token_resource->name,password,false);

    resource.set_string(sha_resurce,token->sha->rendered_text);


    //data/elements/{user}/finite_tokens/{id}/allow_renew
    DtwResource *allow_renew_resource = resource.sub_resource(token_resource, ALLOW_RENEW_PATH);
    resource.set_bool(allow_renew_resource,allow_renew);

    //data/elements/{user}/finite_tokens/{id}/expiration
    DtwResource *expiration_time = resource.sub_resource(token_resource, EXPIRATION_PATH);
    resource.set_long(expiration_time,expiration  *60);

    //data/elements/{user}/finite_tokens/{id}/last_update
    DtwResource *expiration_resource = resource.sub_resource(token_resource, LAST_UPDATE_PATH);
    long now = time(NULL);
    resource.set_long(expiration_resource,now);

    //data/elements/{user}/finite_tokens/{id}/creation
    DtwResource  *creation_resource =resource.sub_resource(token_resource,CREATION_PATH);
    resource.set_long(creation_resource,now);
    return token;


}
Token * database_create_infinite_token(DtwResource *user, const char *password){

    //data/elements/{user}/infinite_tokens/
    DtwResource  *all_tokens = resource.sub_resource(user, INFINITE_TOKENS_PATH);

    //data/elements/{user}/infinite_tokens/{id}
    DtwResource  *token_resource = resource.sub_resource_random(all_tokens,NULL);

    long now = time(NULL);
    //data/elements/{user}/infinite_tokens/{id}/creation
    DtwResource  *creation_resource =resource.sub_resource(token_resource,CREATION_PATH);
    resource.set_long(creation_resource,now);

    //data/elements/{user}/infinite_tokens/{id}/creation
    DtwResource *sha_resource = resource.sub_resource(token_resource,SHA_PATH);
    Token *token = newToken(user->name,token_resource->name,password,true);

    resource.set_string(sha_resource,token->sha->rendered_text);
    //data/elements/{user}/infinite_tokens/{id}/last_update
    DtwResource  *last_update = resource.sub_resource(token_resource,LAST_UPDATE_PATH);
    resource.set_long(last_update,now);
    return token;

}


long count_finite_token(DtwResource *user){
    DtwResource  *all_tokens = resource.sub_resource(user, FINITE_TOKENS_PATH);
    return resource.size(all_tokens);
}

long count_infinite_token(DtwResource *user){
    //data/elements/{user}/infinite_token/
    DtwResource  *all_tokens = resource.sub_resource(user, INFINITE_TOKENS_PATH);
    return resource.size(all_tokens);
}

void remove_last_updated_token(DtwResource *user,const char *token_tipe, int totals){
    //data/elements/{user}/{token_tipe}/
    DtwResource  *all_tokens = resource.sub_resource(user, token_tipe);

    DtwStringArray * elements = resource.list_names(all_tokens);

    for(int v = 0; v < totals; v++){
        DtwResource *last;
        long last_time;
        for(int i = 0; i < elements->size; i++){
            //data/elements/{user}/infinite_token/{i}/
            DtwResource *current = resource.sub_resource(all_tokens,elements->strings[i]);
            //data/elements/{user}/infinite_token/{i}/last_update
            DtwResource *last_update = resource.sub_resource(current,LAST_UPDATE_PATH);
            long  value = resource.get_long(last_update);
            if(value < last_time || i == 0){
                last_time = value;

                last = current;
            }
        }
        resource.destroy(last);
    }

    dtw.string_array.free(elements);

}

void remove_last_updated_infinite_token(DtwResource *user, int totals){
    remove_last_updated_token(user,INFINITE_TOKENS_PATH,totals);

}

void remove_last_updated_finite_token(DtwResource *user, int totals){
    remove_last_updated_token(user,FINITE_TOKENS_PATH,totals);
}


void remove_expired_tokens(DtwResource *user){
    DtwResource  *all_tokens = resource.sub_resource(user, FINITE_TOKENS_PATH);
    DtwStringArray * elements = resource.list_names(all_tokens);
    long now = time(NULL);
    for(int i = 0; i < elements->size; i++){
        DtwResource *current = resource.sub_resource(all_tokens,elements->strings[i]);
        DtwResource *expiration = resource.sub_resource(current,EXPIRATION_PATH);
        long expiration_time = resource.get_long(expiration);
        if(now > expiration_time){
            resource.destroy(current);
        }
    }
    dtw.string_array.free(elements);
}

int database_remove_token(DtwResource *user,Token *token){
    DtwResource  *all_tokens = get_all_tokens_rource(user,token);

    DtwResource *current = resource.sub_resource(all_tokens,"%s",token->token_id);

    if(resource.type(current) == DTW_NOT_FOUND){
        return TOKEN_NOT_EXIST_INTERNAL;
    }
    resource.destroy(current);
    return  FUNCTION_OK;
}

