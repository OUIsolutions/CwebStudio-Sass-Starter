





CwebHttpResponse *create_user(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate_root(request,entries,database);
    if(auth.error){
        return  auth.response_error;
    }

    aply_path_protection(entries, USERNAME_ENTRIE);
    aply_path_protection(entries, EMAIL_ENTRIE);

    char *username = obj.getString(entries, USERNAME_ENTRIE);

    validator.ensure_max_size_by_key(entries,USERNAME_ENTRIE,20);
    validator.ensure_min_size_by_key(entries,USERNAME_ENTRIE,3);

    char *email = obj.getString(entries,EMAIL_ENTRIE);
    validator.ensure_max_size_by_key(entries,EMAIL_ENTRIE,50);
    validator.ensure_min_size_by_key(entries,EMAIL_ENTRIE,10);
    printf("pegou aqui\n");


    char *password = obj.getString(entries, PASSWORD_ENTRIE);
    validator.ensure_min_size_by_key(entries,PASSWORD_ENTRIE,10);


    obj.set_default(entries,IS_ROOT_ENTRIE,hash.newBool(false));
    bool is_root = obj.getBool_converting(entries,IS_ROOT_ENTRIE);

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

    database_create_user(database,username,email,password,is_root);
    CHashObject *response = newCHashObject(
            CODE_KEY,hash.newNumber(INTERNAL_OK),
            MESSAGE_KEY,hash.newString(USER_CREATED)
    );
    resource.commit(database);

    return send_chash_cleaning_memory(response,HTTP_CREATED);
}