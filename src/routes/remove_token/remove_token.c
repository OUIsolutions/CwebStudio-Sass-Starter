

CwebHttpResponse *remove_token(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate(request,entries,database);
    if(auth.error){
        return  auth.response_error;
    }
    DtwResource *user = auth.user;

    char *token = obj.getString(entries,TOKEN_ENTRIE);
    database_remove_token(user,token);

    CHashObject *response = newCHashObject(
            CODE_KEY,hash.newNumber(INTERNAL_OK),
            MESSAGE_KEY,hash.newString(TOKEN_CREATED)
    );
    resource.commit(database);

    return send_chash_cleaning_memory(response,HTTP_CREATED);

}