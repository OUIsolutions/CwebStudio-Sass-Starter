

CwebHttpResponse *modify_user_props(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate_root(request,entries,database);
    if(auth.error){
        return  auth.response_error;
    }

    char *username_or_email = obj.getString(entries, USERNAME_OR_EMAIL_ENTRE);

    CHash_catch(entries){
        return send_entrie_error(request, entries);
    }


    char *new_username = NULL;
    char *new_email = NULL;
    char *new_password = NULL;
    bool set_is_root = false;
    bool is_root = false;


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

    if(obj.exist(entries, IS_ROOT_ENTRE)){
        set_is_root = true;
        is_root = obj.getBool_converting(entries, IS_ROOT_ENTRE);
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


    if(!new_username && !new_email && !new_password && !set_is_root){
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

    DtwResource *user = find_user_by_username_or_email(database,username_or_email);

    if(!user){
        return send_error(
                request,
                NOT_FOUND,
                USER_NOT_EXIST,
                USER_NOT_EXIST_MENSSAGE,
                username_or_email
        );
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
    database_modify_user(database,user,new_username,new_email,new_password,set_is_root,is_root);

    CHashObject *response = newCHashObject(
            CODE_KEY,hash.newNumber(INTERNAL_OK),
            MESSAGE_KEY,hash.newString(USER_MODIFIED)
    );
    resource.commit(database);

    return send_chash_cleaning_memory(response,HTTP_CREATED);




}