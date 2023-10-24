

CwebHttpResponse *modify_self_props(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate(request,entries,database);
    if(auth.error){
        return  auth.response_error;
    }

    DtwResource *user = auth.user;

    char *new_username = NULL;
    char *new_email = NULL;
    char *new_password = NULL;


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

    if(new_username && new_email){
        if(strcmp(new_username,new_email) ==0){
            validator.raise_error(
                    entries,
                    EMAIL_CANNOT_BE_EQUAL_TO_USERNAME,
                    EMAIL_CANNOT_BE_EQUAL_TO_USERNAME_MESSAGE,
                    NULL
            );
        }
    }

    if(!new_username && !new_email && !new_password){
        validator.raise_error(
                entries,
                NOTHING_TO_MODIFY,
                NOTHING_TO_MODIFY_MESSAGE,
                NULL
        );
    }



    CHash_catch(entries){
        return send_entrie_error(request, entries);
    }


    if(new_username){
        DtwResource *already_exist_username = find_user_by_username_or_email(database,new_username);
        if(already_exist_username){
            return send_error(
                    request,
                    CONFLICT,
                    USER_ALREADY_EXIST,
                    USER_ALREADY_MESSAGE,
                    new_username
            );
        }
    }
    if(new_email){
        DtwResource *already_exist_email = find_user_by_username_or_email(database,new_email);
        if(already_exist_email){
            return send_error(
                    request,
                    CONFLICT,
                    USER_ALREADY_EXIST,
                    USER_ALREADY_MESSAGE,
                    new_email
            );
        }
    }

    database_modify_user(database,user,new_username,new_email,new_password,false,false);

    CHashObject *response = newCHashObject(
            CODE_KEY,hash.newNumber(INTERNAL_OK),
            MESSAGE_KEY,hash.newString(USER_MODIFIED)
    );
    resource.commit(database);

    return send_chash_cleaning_memory(response,HTTP_CREATED);




}