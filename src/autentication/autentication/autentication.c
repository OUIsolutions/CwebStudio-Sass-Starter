

Autentication autenticate(CwebHttpRequest *request, CHash *entries,DtwResource *database){

    Autentication auth = {0};
    char *token = obj.getString(entries,TOKEN);

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
    DtwResource *user = find_user_by_id(database, token_obj->user_id);
    #ifdef ALLOW_LOCKER
        resource.lock(user);
    #endif

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

    DtwResource *token_resource = NULL;
    if(token_obj->infinite){
        token_resource = get_ifinite_token(user,token);
    }

    if(token_obj->infinite == false){
        token_resource = get_finite_token(user,token);
    }

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

    if(token_obj->infinite){
        DtwResource *last_update = resource.sub_resource(token_resource,LAST_UPDATE_PATH);
        resource.set_long(last_update, time(NULL));
    }

    if(token_obj->infinite == false){
        DtwResource *expiration = resource.sub_resource(token_resource,EXPIRATION_PATH);
        long value = resource.get_long(expiration);
        long now = time(NULL);
        if(now > value){
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
    }

    Token_free(token_obj);
    auth.user = user;
    return auth;
}
