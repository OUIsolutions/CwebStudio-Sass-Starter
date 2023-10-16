

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
                INVALID_TOKEN,
                INVALID_TOKEN,
                NOT_VALID_TOKEN_MESSAGE,
                token
        );
        return auth;
    }
    DtwResource *user = find_user_by_id(database, token_obj->user_id);
    printf("pegou aqui\n");

    if(!user){
        auth.error = true;
        auth.response_error =send_error(
                request,
                INVALID_TOKEN,
                INVALID_TOKEN,
                NOT_VALID_TOKEN_MESSAGE,
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
                INVALID_TOKEN,
                INVALID_TOKEN,
                NOT_VALID_TOKEN_MESSAGE,
                token
        );
        Token_free(token_obj);
        return auth;
    }


    Token_free(token_obj);
    auth.user = user;
    return auth;
}
