

CwebHttpResponse *remove_token(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate(request,entries,database);
    if(auth.error){
        return  auth.response_error;
    }
    DtwResource *user = auth.user;

    char *token_to_remove = obj.getString(entries, TOKEN_TO_REMOVE_ENTRE);
    CHash_catch(entries){
        return send_entrie_error(request, entries);
    }

    Token *t = extract_token(token_to_remove);
    if(!t){
        return send_error(
                request,
                BAD_REQUEST,
                INVALID_TOKEN,
                NOT_VALID_TOKEN_MESSAGE,
                token_to_remove
        );
    }

    if(database_remove_token(user,t)){
        Token_free(t);
        return send_error(
                request,
                BAD_REQUEST,
                INVALID_TOKEN,
                NOT_EXIST_TOKEN_MESSAGE,
                token_to_remove
        );
    }

    Token_free(t);

    CHashObject *response = newCHashObject(
            CODE_KEY,hash.newNumber(INTERNAL_OK),
            MESSAGE_KEY,hash.newString(TOKEN_REMOVED)
    );
    commit_transaction(database);

    return send_chash_cleaning_memory(response,HTTP_CREATED);

}