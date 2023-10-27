

CwebHttpResponse *remove_all_infinite_tokens(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate(request,entries,database);
    if(auth.error){
        return  auth.response_error;
    }
    DtwResource *user = auth.user;

    DtwResource *finite_tokens = resource.sub_resource(user,INFINITE_TOKENS_PATH);
    resource.destroy(finite_tokens);

    resource.commit(database);

    CHashObject *response = newCHashObject(
            CODE_KEY,hash.newNumber(INTERNAL_OK),
            MESSAGE_KEY,hash.newString(ALL_TOKENS_REMOVED)
    );

    return send_chash_cleaning_memory(response,HTTP_CREATED);

}