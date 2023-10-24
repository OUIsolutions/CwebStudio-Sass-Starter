

CwebHttpResponse *modify_self_props(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate(request,entries,database);
    if(auth.error){
        return  auth.response_error;
    }

    DtwResource *user = auth.user;

    char *new_username = NULL;
    char *new_email = NULL;
    char *new_password = NULL;
    char *password = NULL;

    if(obj.exist(entries, NEW_USERNAME_ENTRE)){
        aply_path_protection(entries, NEW_USERNAME_ENTRE);
        validator.ensure_max_size_by_key(entries, NEW_USERNAME_ENTRE, 20);
        validator.ensure_min_size_by_key(entries, NEW_USERNAME_ENTRE, 3);
        new_username = obj.getString(entries, NEW_USERNAME_ENTRE);
    }

    if(obj.exist(entries, NEW_EMAIL_ENTRE)){
        aply_path_protection(entries, NEW_EMAIL_ENTRE);
        validator.ensure_max_size_by_key(entries, NEW_EMAIL_ENTRE, 50);
        validator.ensure_min_size_by_key(entries, NEW_EMAIL_ENTRE, 10);
        new_email = obj.getString(entries, NEW_EMAIL_ENTRE);
    }

    if(obj.exist(entries, NEW_PASSWORD_ENTRE)){
        validator.ensure_min_size_by_key(entries, NEW_PASSWORD_ENTRE, 10);
        validator.ensure_max_size_by_key(entries, NEW_PASSWORD_ENTRE, 50);
        new_password = obj.getString(entries, NEW_PASSWORD_ENTRE);
    }

    if(strings_equal(new_username,new_email)){
        validator.raise_error(
                entries,
                EMAIL_CANNOT_BE_EQUAL_TO_USERNAME,
                EMAIL_CANNOT_BE_EQUAL_TO_USERNAME_MESSAGE,
                NULL
        );
    }


    if(!new_username && !new_email && !new_password){
        validator.raise_error(
                entries,
                NOTHING_TO_MODIFY,
                NOTHING_TO_MODIFY_MESSAGE,
                NULL
        );

    }
    bool require_password = new_password || new_email;
    if(require_password){
        password = obj.getString(entries,PASSWORD_ENTRE);

    }

    CHash_catch(entries){
        return send_entrie_error(request, entries);
    }

    if(!password_are_equal_if_password_provided(user, password)){
        return send_error(
                request,
                FOREBIDEN,
                WRONG_PASSWORD,
                WRONG_PASSWORD_MENSSAGE
        );
    }



   int status_username = get_user_index_status_if_new_value_provided(database, user, USERNAME_PATH, new_username);
    if(status_username == USER_ALREADY_EXIST_INTERNAl){
        return send_error(
                request,
                CONFLICT,
                USER_ALREADY_EXIST,
                USER_ALREADY_MESSAGE,
                new_username
        );
    }
    if(status_username == USER_HAVE_THE_SAME_NAME_INTERNAL){
        new_username = NULL;
    }


    int status_email = get_user_index_status_if_new_value_provided(database, user, EMAIL_PATH, new_email);
    if(status_email ==USER_ALREADY_EXIST_INTERNAl ){
        return send_error(
                request,
                CONFLICT,
                USER_ALREADY_EXIST,
                USER_ALREADY_MESSAGE,
                new_email
        );
    }
    if(status_email == USER_HAVE_THE_SAME_NAME_INTERNAL){
        new_email = NULL;
    }


    if(!new_username && !new_email && !new_password){
        validator.raise_error(
                entries,
                NOTHING_TO_MODIFY,
                NOTHING_TO_MODIFY_MESSAGE,
                NULL
        );
        return send_entrie_error(request, entries);

    }

    database_modify_user(database,user,new_username,new_email,new_password,false,false);

    CHashObject *response = newCHashObject(
            CODE_KEY,hash.newNumber(INTERNAL_OK),
            MESSAGE_KEY,hash.newString(USER_MODIFIED)
    );
    resource.commit(database);

    return send_chash_cleaning_memory(response,HTTP_CREATED);




}