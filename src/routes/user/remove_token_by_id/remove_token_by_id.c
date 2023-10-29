

CwebHttpResponse *remove_token_by_id(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate(request,entries,database);
    if(auth.error){
        return  auth.response_error;
    }

    DtwResource *user = auth.user;
    char *token_id = obj.getString(entries,TOKEN_TO_REMOVE_ENTRE);
    CHash_catch(entries){
        return send_entrie_error(request, entries);
    }

    DtwResource *finite_tokens = resource.sub_resource(user,FINITE_TOKENS_PATH);
    DtwResource *possible_finite_token = resource.sub_resource(finite_tokens,token_id);
    bool token_is_finite = resource.type(possible_finite_token) ==DTW_FOLDER_TYPE;
    if(token_is_finite){
        resource.destroy(possible_finite_token);
        CHashObject *response = newCHashObject(
                CODE_KEY,hash.newNumber(INTERNAL_OK),
                MESSAGE_KEY,hash.newString(TOKEN_REMOVED)
        );
        commit_transaction(database,SAVE_TOKEN_TRANSACTIONS);
        return send_chash_cleaning_memory(response,HTTP_CREATED);
    }

    DtwResource *infinite_tokens =  resource.sub_resource(user,INFINITE_TOKENS_PATH);
    DtwResource *possible_infinite_token = resource.sub_resource(infinite_tokens,token_id);
    bool token_is_ifinite = resource.type(possible_infinite_token) == DTW_FOLDER_TYPE;
    if(token_is_ifinite){
        resource.destroy(possible_infinite_token);
        CHashObject *response = newCHashObject(
                CODE_KEY,hash.newNumber(INTERNAL_OK),
                MESSAGE_KEY,hash.newString(TOKEN_REMOVED)
        );
        commit_transaction(database,SAVE_TOKEN_TRANSACTIONS);

        return send_chash_cleaning_memory(response,HTTP_CREATED);
    }

    return send_error(
            request,
            NOT_FOUND,
            INVALID_TOKEN,
            NOT_EXIST_TOKEN_MESSAGE,
            token_id
    );

}