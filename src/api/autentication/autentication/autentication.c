


Autentication autenticate(CwebHttpRequest *request, CHash *entries,DtwResource *database){

    Autentication auth = {0};
    char *token = obj.getString(entries, TOKEN_ENTRE);

    CHash_catch(entries){
        auth.error = true;
        auth.response_error = send_entrie_error(request, entries);
        return auth;
    }
    UniversalGarbage  *garbage = newUniversalGarbage();
    Token *token_obj = extract_token(token);

    UniversalGarbage_add(garbage,Token_free,token_obj);

    if(!token_obj){
        auth.error = true;
        auth.response_error =send_error(
                request,
                BAD_REQUEST,
                INVALID_TOKEN,
                NOT_VALID_TOKEN_MESSAGE,
                token
        );

        UniversalGarbage_free(garbage);
        return auth;
    }

    DtwResource *user = find_user_by_id(database, token_obj->user_id->rendered_text);
    DtwResource_catch(database){
        UniversalGarbage_free(garbage);
        return auth;
    }
    if(!user){
        auth.error = true;
        auth.response_error =send_error(
                request,
                NOT_FOUND,
                INVALID_TOKEN,
                NOT_EXIST_TOKEN_MESSAGE,
                token
        );
        UniversalGarbage_free(garbage);
        return auth;
    }

    resource.set_long_in_sub_resource(user, dtw_get_time(),LAST_UPDATE_PATH);

    DtwResource *token_resource = get_token_resource(user,token_obj);
    DtwResource_catch(database){
        UniversalGarbage_free(garbage);
        return auth;
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
        UniversalGarbage_free(garbage);
        return auth;
    }

    char *sha = resource.get_string_from_sub_resource(token_resource,SHA_PATH);
    DtwResource_catch(database){
        UniversalGarbage_free(garbage);
        return auth;
    }
    if(!strings_equal(sha,token_obj->sha->rendered_text)){
        auth.error = true;
        auth.response_error =send_error(
                request,
                NOT_FOUND,
                INVALID_TOKEN,
                NOT_VALID_TOKEN_MESSAGE,
                token
        );
        UniversalGarbage_free(garbage);
        return auth;
    }

    if(token_obj->infinite){
        DtwResource *last_update = resource.sub_resource(token_resource,LAST_UPDATE_PATH);
        resource.set_long(last_update, dtw_get_time());
    }

    if(token_obj->infinite == false){
        DtwResource *expiration = resource.sub_resource(token_resource,EXPIRATION_PATH);
        long expiration_Value = resource.get_long(expiration);
        DtwResource *last_update = resource.sub_resource(token_resource,LAST_UPDATE_PATH);
        long last_update_value = resource.get_long(last_update);

        DtwResource_catch(database){
            UniversalGarbage_free(garbage);
            return auth;
        }
        long now = dtw_get_time();

        if(now > (expiration_Value + last_update_value)){
            auth.error = true;
            auth.response_error =send_error(
                    request,
                    FOREBIDEN,
                    INVALID_TOKEN,
                    EXPIRED_TOKEN_MESSAGE,
                    token
            );
            UniversalGarbage_free(garbage);
            return auth;
        }

        bool allow_renew = resource.get_bool(
                resource.sub_resource(token_resource,ALLOW_RENEW_PATH)
        );
        if(allow_renew){
            resource.set_long(last_update, dtw_get_time());
        }


    }

    UniversalGarbage_free(garbage);
    auth.user = user;
    return auth;
}

Autentication autenticate_sub_token_or_token(CwebHttpRequest *request, CHash *entries, DtwResource *database, const char *seed){

    //we try to autenticate with the first token before
    if(obj.exist(entries,TOKEN_ENTRE)){
        return autenticate(request,entries,database);
    }

    Autentication auth = {0};
    char *token = obj.getString(entries, SUB_TOKEN_ENTRE);

    CHash_catch(entries){
        auth.error = true;
        auth.response_error = send_entrie_error(request, entries);
        return auth;
    }
    UniversalGarbage *garbage = newUniversalGarbage();
    Token *token_obj = extract_token(token);
    UniversalGarbage_add(garbage, Token_free,token_obj);

    if(!token_obj){
        auth.error = true;
        auth.response_error =send_error(
                request,
                BAD_REQUEST,
                INVALID_TOKEN,
                NOT_VALID_TOKEN_MESSAGE,
                token
        );
        UniversalGarbage_free(garbage);
        return auth;
    }

    DtwResource *user = find_user_by_id(database, token_obj->user_id->rendered_text);
    DtwResource_catch(database){
        UniversalGarbage_free(garbage);
        return auth;
    }

    if(!user){
        auth.error = true;
        auth.response_error =send_error(
                request,
                NOT_FOUND,
                INVALID_TOKEN,
                NOT_EXIST_TOKEN_MESSAGE,
                token
        );
        UniversalGarbage_free(garbage);
        return auth;
    }

    DtwResource *token_resource = get_token_resource(user,token_obj);
    DtwResource_catch(database){
        UniversalGarbage_free(garbage);
        return auth;
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
        UniversalGarbage_free(garbage);
        return auth;
    }

    char *sha = resource.get_string_from_sub_resource(token_resource,SHA_PATH);
    DtwResource_catch(database){
        UniversalGarbage_free(garbage);
        return auth;
    }

    //subtokens age generated by sha + seed
    DtwHash *dt_hash = newDtwHash();
    UniversalGarbage_add(garbage, DtwHash_free,dt_hash);

    dtw.hash.digest_string(dt_hash,sha);
    dtw.hash.digest_string(dt_hash,seed);
    CTextStack * sha_stack= stack.newStack_string(dt_hash->hash);
    UniversalGarbage_add(garbage, CTextStack_free,sha_stack);
    stack.self_substr(sha_stack,0,SHA_SIZE);
    bool sha_equal = strings_equal(sha_stack->rendered_text,token_obj->sha->rendered_text);


    if(!sha_equal){
        auth.error = true;
        auth.response_error =send_error(
                request,
                NOT_FOUND,
                INVALID_TOKEN,
                NOT_VALID_TOKEN_MESSAGE,
                token
        );
        UniversalGarbage_free(garbage);
        return auth;
    }

    if(token_obj->infinite == false){
        DtwResource *expiration = resource.sub_resource(token_resource,EXPIRATION_PATH);
        DtwResource *last_update = resource.sub_resource(token_resource,LAST_UPDATE_PATH);
        long expiration_Value = resource.get_long(expiration);
        long last_update_value = resource.get_long(last_update);
        DtwResource_catch(database){
            UniversalGarbage_free(garbage);
            return auth;
        }

        long now = dtw_get_time();
        bool expired = now > (expiration_Value + last_update_value);
        if(expired){
            auth.error = true;
            auth.response_error =send_error(
                    request,
                    FOREBIDEN,
                    INVALID_TOKEN,
                    EXPIRED_TOKEN_MESSAGE,
                    token
            );
            UniversalGarbage_free(garbage);
            return auth;
        }

    }

    auth.user = user;
    UniversalGarbage_free(garbage);
    return auth;
}


Autentication autenticate_root(CwebHttpRequest *request, CHash *entries,DtwResource *database){
    Autentication auth = autenticate(request,entries,database);
    DtwResource_catch(database){
        return auth;
    }
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