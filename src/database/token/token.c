


void set_finity_token(DtwResource *user, char *token, bool allow_renew, int expiration){

    //user/finite_token/
    DtwResource  *all_tokens = resource.sub_resource(user, FINITE_TOKEN_PATH);
    //user/token/akspdih3u2ju223j2j3j2
    DtwResource  *token_resource = resource.sub_resource(all_tokens,token);
    //user/token/akspdih3u2ju223j2j3j2/allow_renew
    DtwResource *allow_reenew_resource = resource.sub_resource(token_resource, ALLOW_RENEW);
    resource.set_bool(allow_reenew_resource,allow_renew);

    DtwResource *expiration_resource = resource.sub_resource(token_resource, EXPIRATION_PATH);
    long now = time(NULL);
    resource.set_long(expiration_resource,now + (expiration * 60));

    DtwResource  *creation_resource =resource.sub_resource(token_resource,CREATION_PATH);
    resource.set_long(creation_resource,now);

}

void set_infinity_token(DtwResource *user, char *token){

    //user/infinite_token/
    DtwResource  *all_tokens = resource.sub_resource(user, INFINITE_TOKEN_PATH);
    //user/token/akspdih3u2ju223j2j3j2
    DtwResource  *token_resource = resource.sub_resource(all_tokens,token);
    long now = time(NULL);
    DtwResource  *creation_resource =resource.sub_resource(token_resource,CREATION_PATH);
    resource.set_long(creation_resource,now);

}

long count_infinite_token(DtwResource *user){
    DtwResource  *all_tokens = resource.sub_resource(user, INFINITE_TOKEN_PATH);
    return resource.size(all_tokens);
}

void remove_last_infinite_token(DtwResource *user){
    DtwResource  *all_tokens = resource.sub_resource(user, INFINITE_TOKEN_PATH);
    DtwStringArray * elements = resource.list_names(all_tokens);

    DtwResource *last;
    long last_time;
    for(int i = 0; i < elements->size; i++){
        DtwResource *current = resource.sub_resource(all_tokens,elements->strings[i]);
        DtwResource *creation  =  resource.sub_resource(current,CREATION_PATH);
        long  value = resource.get_long(creation);
        if(value < last_time){
            last_time = value;
            last = current;
        }
    }
    resource.destroy(last);
}

long count_finite_token(DtwResource *user){
    DtwResource  *all_tokens = resource.sub_resource(user, FINITE_TOKEN_PATH);
    return resource.size(all_tokens);
}

