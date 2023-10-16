

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
        validator.raise_error_by_key(entries,
                 TOKEN,
                 INVALID_TOKEN,
                 NOT_VALID_TOKEN_MESSAGE,
                 NULL
        );
    }

    CHash_catch(entries){
        auth.error = true;
        auth.response_error = send_entrie_error(request, entries);
        return auth;
    }
    DtwResource *user = find_user_by_id(database, token_obj->user_id);

    
    return auth;
}
