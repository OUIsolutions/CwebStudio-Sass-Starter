





CwebHttpResponse *self_remove(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate(request,entries,database);
    if(auth.error){
        return  auth.response_error;
    }
    DtwResource *user = auth.user;


    char *password = obj.getString(entries, PASSWORD_ENTRIE);
    CHash_catch(entries){
        return send_entrie_error(request, entries);
    }

    if(!password_are_equal(user, password)){
        return send_error(
                request,
                FOREBIDEN,
                WRONG_PASSWORD,
                WRONG_PASSWORD_MENSSAGE
        );
    }

    database_remove_user(database,user);

    CHashObject *response = newCHashObject(
            CODE_KEY,hash.newNumber(INTERNAL_OK),
            MESSAGE_KEY,hash.newString(USER_REMOVED)
    );
    resource.commit(database);

    return send_chash_cleaning_memory(response,HTTP_CREATED);
}