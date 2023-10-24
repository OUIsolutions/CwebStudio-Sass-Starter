

Autentication autenticate(CwebHttpRequest *request, CHash *entries,DtwResource *database){

    Autentication auth = {0};
    char *token = obj.getString(entries, TOKEN_ENTRIE);

    CHash_catch(entries){
        auth.error = true;
        auth.response_error = send_entrie_error(request, entries);
        return auth;
    }

    Token *token_obj = extract_token(token);
    if(!token_obj){
        auth.error = true;
        auth.response_error =send_error(
                request,
                BAD_REQUEST,
                INVALID_TOKEN,
                NOT_VALID_TOKEN_MESSAGE,
                token
        );
        return auth;
    }
    DtwResource *user = find_user_by_id(database, token_obj->user_id->rendered_text);


    if(!user){
        auth.error = true;
        auth.response_error =send_error(
                request,
                NOT_FOUND,
                INVALID_TOKEN,
                NOT_EXIST_TOKEN_MESSAGE,
                token
        );
        Token_free(token_obj);
        return auth;
    }

    DtwResource *token_resource = get_token_resource(user,token_obj);

    if(!token_resource){
        auth.error = true;
        auth.response_error =send_error(
                request,
                NOT_FOUND,
                INVALID_TOKEN,
                NOT_EXIST_TOKEN_MESSAGE,
                token
        );
        Token_free(token_obj);

        return auth;
    }
    char *sha = resource.get_string_from_sub_resource(token_resource,SHA_PATH);
    if(strcmp(sha,token_obj->sha->rendered_text) != 0){
        auth.error = true;
        auth.response_error =send_error(
                request,
                NOT_FOUND,
                INVALID_TOKEN,
                NOT_VALID_TOKEN_MESSAGE,
                token
        );
        Token_free(token_obj);
        return auth;
    }

    if(token_obj->infinite){
        DtwResource *last_update = resource.sub_resource(token_resource,LAST_UPDATE_PATH);
        resource.set_long(last_update, time(NULL));
    }

    if(token_obj->infinite == false){
        DtwResource *expiration = resource.sub_resource(token_resource,EXPIRATION_PATH);
        long expiration_Value = resource.get_long(expiration);
        DtwResource *last_update = resource.sub_resource(token_resource,LAST_UPDATE_PATH);
        long last_update_value = resource.get_long(last_update);
        long now = time(NULL);
        if(now > (expiration_Value + last_update_value)){
            auth.error = true;
            auth.response_error =send_error(
                    request,
                    FOREBIDEN,
                    INVALID_TOKEN,
                    EXPIRED_TOKEN_MESSAGE,
                    token
            );
            Token_free(token_obj);
            return auth;
        }
        bool allow_renew = resource.get_bool(
                resource.sub_resource(token_resource,ALLOW_RENEW_PATH)
        );
        if(allow_renew){
            resource.set_long(last_update, time(NULL));
        }


    }

    Token_free(token_obj);
    auth.user = user;
    return auth;
}


Autentication autenticate_root(CwebHttpRequest *request, CHash *entries,DtwResource *database){
    Autentication auth = autenticate(request,entries,database);
    if(auth.error){
        return auth;
    }
    if(!is_root(auth.user)){
        auth.error = true;
        auth.response_error =send_error(
                request,
                FOREBIDEN,
                USER_NOT_ROOT,
                USER_NOT_ROOT_MESSAGE
        );
    }
    return  auth;;
}