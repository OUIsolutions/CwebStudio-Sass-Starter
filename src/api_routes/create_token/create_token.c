

CwebHttpResponse *create_token(CwebHttpRequest *request ){

    CHashObject * entries = join_headders_and_paramns(request);
    char *username_or_email = obj.getString(entries,USERNAME_OR_EMAIL);
    char *password = obj.getString(entries,PASSWORD);

    if(hash.errors(entries)){
        return send_entrie_error_cleaning_memory(request,entries);
    }

    DtwResource *user = find_user_by_username_or_email(username_or_email,true);
    if(!user){
        return send_error(
                request,
                NOT_FOUND,
                ROUTE_NOT_FOUND,
                USER_NOT_EXIST_MENSSAGE
        );
    }

    return cweb.response.send_text("ok",200);



}