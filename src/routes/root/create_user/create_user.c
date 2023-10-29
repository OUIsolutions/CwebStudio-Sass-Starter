





CwebHttpResponse *create_user(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate_root(request,entries,database);
    if(auth.error){
        return  auth.response_error;
    }


    char *username = obj.getString(entries, USERNAME_ENTRE);

    validator.ensure_max_size_by_key(entries, USERNAME_ENTRE, 20);
    validator.ensure_min_size_by_key(entries, USERNAME_ENTRE, 3);

    char *email = obj.getString(entries, EMAIL_ENTRE);
    validator.ensure_max_size_by_key(entries, EMAIL_ENTRE, 50);
    validator.ensure_min_size_by_key(entries, EMAIL_ENTRE, 10);


    char *password = obj.getString(entries, PASSWORD_ENTRE);
    validator.ensure_min_size_by_key(entries, PASSWORD_ENTRE, 10);
    validator.ensure_max_size_by_key(entries, PASSWORD_ENTRE, 50);

    obj.set_default(entries, IS_ROOT_ENTRE, hash.newBool(false));
    bool is_root = obj.getBool_converting(entries, IS_ROOT_ENTRE);


    obj.set_default(entries, VERIFIED_ENTRE, hash.newBool(false));



    bool verified = obj.getBool_converting(entries,VERIFIED_ENTRE);
    CHash_protected(entries){
        if(strcmp(username,email) ==0){
            validator.raise_error(
                    entries,
                    EMAIL_CANNOT_BE_EQUAL_TO_USERNAME,
                    EMAIL_CANNOT_BE_EQUAL_TO_USERNAME_MESSAGE,
                    NULL
            );
        }
    }


    CHash_catch(entries){
        return send_entrie_error(request, entries);
    }

    DtwResource *already_exist_email = find_user_by_username_or_email(database,email);

    if(already_exist_email){
        return send_error(
                request,
                CONFLICT,
                USER_ALREADY_EXIST,
                USER_ALREADY_MESSAGE,
                email
        );
    }
    DtwResource *already_exist_username = find_user_by_username_or_email(database,username);

    if(already_exist_username){
        return send_error(
                request,
                CONFLICT,
                USER_ALREADY_EXIST,
                USER_ALREADY_MESSAGE,
                username
        );
    }

    database_create_user(database,username,email, password,is_root,verified);

    CHashObject *response = newCHashObject(
            CODE_KEY,hash.newNumber(INTERNAL_OK),
            MESSAGE_KEY,hash.newString(USER_CREATED)
    );
    commit_transaction(database);
    return send_chash_cleaning_memory(response,HTTP_CREATED);
}