





CwebHttpResponse *remove_user(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate_root(request,entries,database);
    if(auth.error){
        return  auth.response_error;
    }

    char *username_or_email = obj.getString(entries, USERNAME_OR_EMAIL_ENTRE);

    CHash_catch(entries){
        return send_entrie_error(request, entries);
    }

    DtwResource *user_to_remove = find_user_by_username_or_email(database,username_or_email);

    if(!user_to_remove){
        return send_error(
                request,
                NOT_FOUND,
                USER_NOT_EXIST,
                USER_NOT_EXIST_MENSSAGE,
                username_or_email
        );
    }

    database_remove_user(database,user_to_remove);


    CHashObject *response = newCHashObject(
            CODE_KEY,hash.newNumber(INTERNAL_OK),
            MESSAGE_KEY,hash.newString(USER_REMOVED)
    );
    resource.commit(database);

    return send_chash_cleaning_memory(response,HTTP_CREATED);
}