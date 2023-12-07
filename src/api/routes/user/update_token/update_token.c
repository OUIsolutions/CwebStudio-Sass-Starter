



CwebHttpResponse *update_token(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate(request,entries,database);
    DtwResource_catch(database){
        return NULL;
    }
    commit_transaction(database);

    CHashObject *response = newCHashObject(
            CODE_KEY,hash.newNumber(INTERNAL_OK),
            MESSAGE_KEY,hash.newString(TOKEN_UPDATED)
    );

    return send_chash_cleaning_memory(response,HTTP_CREATED);
}