

CwebHttpResponse *create_token(CwebHttpRequest *request ){

    CHashObject * entries = join_headders_and_paramns(request);
    char *username_or_email = obj.getString(entries,USERNAME_OR_EMAIL);
    char *password = obj.getString(entries,PASSWORD);

    if(hash.errors(entries)){
        return send_entrie_error_cleaning_memory(request,entries);
    }
    DtwResource *database = resource.newResource(DATABASE_PATH);
    DtwResource *user = find_user_by_username_or_email(database,username_or_email,true);

    if(!user){
        resource.free(database);
        return send_error(
                request,
                NOT_FOUND,
                USER_NOT_EXIST,
                USER_NOT_EXIST_MENSSAGE,
                username_or_email
        );
    }

    if(!password_are_equal(user, password)){
        resource.free(database);
        return send_error(
                request,
                FOREBIDEN,
                WRONG_PASSWORD,
                WRONG_PASSWORD_MENSSAGE
        );
    }

    resource.commit(database);
    resource.free(database);

    return cweb.response.send_text("ok",200);



}