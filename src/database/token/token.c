


void set_finity_token(DtwResource *user, char *token, bool allow_renew, int expiration){

    //data/elements/user/finite_token/
    DtwResource  *all_tokens = resource.sub_resource(user, FINITE_TOKEN_PATH);
    //data/elements/user/token/akspdih3u2ju223j2j3j2
    DtwResource  *token_resource = resource.sub_resource(all_tokens,token);
    //data/elements/user/token/akspdih3u2ju223j2j3j2/renew_time

    if(allow_renew){
        DtwResource *renew_time = resource.sub_resource(token_resource, RENEW_TIME);
        resource.set_long(renew_time,expiration);
    }

    DtwResource *expiration_resource = resource.sub_resource(token_resource, EXPIRATION_PATH);
    long now = time(NULL);
    resource.set_long(expiration_resource,now + (expiration * 60));

    DtwResource  *creation_resource =resource.sub_resource(token_resource,CREATION_PATH);
    resource.set_long(creation_resource,now);

}

void set_infinity_token(DtwResource *user, char *token){

    //data/elements/user/infinite_token/
    DtwResource  *all_tokens = resource.sub_resource(user, INFINITE_TOKEN_PATH);
    //data/elements/user/token/akspdih3u2ju223j2j3j2
    DtwResource  *token_resource = resource.sub_resource(all_tokens,token);
    long now = time(NULL);
    //data/elements/user/token/akspdih3u2ju223j2j3j2/creation
    DtwResource  *creation_resource =resource.sub_resource(token_resource,CREATION_PATH);
    resource.set_long(creation_resource,now);

}

long count_infinite_token(DtwResource *user){
    //data/elements/user/infinite_token/
    DtwResource  *all_tokens = resource.sub_resource(user, INFINITE_TOKEN_PATH);
    return resource.size(all_tokens);
}

void remove_last_infinite_token(DtwResource *user){
    //data/elements/user/finite_token/
    DtwResource  *all_tokens = resource.sub_resource(user, INFINITE_TOKEN_PATH);
    DtwStringArray * elements = resource.list_names(all_tokens);

    DtwResource *last;
    long last_time;
    for(int i = 0; i < elements->size; i++){
        DtwResource *current = resource.sub_resource(all_tokens,elements->strings[i]);
        DtwResource *creation = resource.sub_resource(current,CREATION_PATH);
        long  value = resource.get_long(creation);
        if(value < last_time || i == 0){
            last_time = value;

            last = current;
        }
    }
z
    resource.destroy(last);
    dtw.string_array.free(elements);

}

long count_finite_token(DtwResource *user){
    DtwResource  *all_tokens = resource.sub_resource(user, FINITE_TOKEN_PATH);
    return resource.size(all_tokens);
}

