





CwebHttpResponse *self_remove(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate(request,entries,database);
    if(auth.error){
        return  auth.response_error;
    }
    DtwResource *user = auth.user;

    database_remove_user(database,user);

    CHashObject *response = newCHashObject(
            CODE_KEY,hash.newNumber(INTERNAL_OK),
            MESSAGE_KEY,hash.newString(USER_REMOVED)
    );
    resource.commit(database);

    return send_chash_cleaning_memory(response,HTTP_CREATED);
}