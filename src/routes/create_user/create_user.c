





CwebHttpResponse *create_user(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate_root(request,entries,database);
    if(auth.error){
        return  auth.response_error;
    }

    aply_path_protection(entries, USERNAME_KEY);
    aply_path_protection(entries, EMAIL_KEY);

    char *username = obj.getString(entries, USERNAME_KEY);
    char *email = obj.getString(entries,EMAIL_KEY);
    char *password = obj.getString(entries, PASSWORD_ENTRIE);

    obj.set_default(entries,IS_ROOT_KEY,hash.newBool(false));
    bool is_root = obj.getBool_converting(entries,IS_ROOT_KEY);


    CHash_catch(entries){
        return send_entrie_error(request, entries);
    }

    DtwResource *already_exist_email = find_user_by_username_or_email(database,email);

    if(already_exist_email){
        return send_error(
                request,
                CONFLICT,
                USER_NOT_EXIST,
                USER_ALREADY_MESSAGE,
                email
        );
    }
    DtwResource *already_exist_username = find_user_by_username_or_email(database,username);

    if(already_exist_username){
        return send_error(
                request,
                CONFLICT,
                USER_NOT_EXIST,
                USER_ALREADY_MESSAGE,
                username
        );
    }

    database_create_user(database,username,email,password);
    CHashObject *response = newCHashObject(
            CODE_KEY,hash.newNumber(INTERNAL_OK),
            MESSAGE_KEY,hash.newString(USER_CREATED)
    );
    resource.commit(database);

    return send_chash_cleaning_memory(response,HTTP_CREATED);
}