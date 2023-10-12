

CwebHttpResponse *create_token(CwebHttpRequest *request ){

    CHashObject * entries = join_headders_and_paramns(request);
    char *username_or_email = obj.getString(entries,USERNAME_OR_EMAIL);
    char *password = obj.getString(entries,PASSWORD);

    if(hash.errors(entries)){
        return send_entrie_error_cleaning_memory(request,entries);
    }

    DtwResource *database = resource.newResource(DATABASE_PATH);
    DtwResource *users = resource.sub_resource(database, USERS_PATH);
    char * id = find_element_by_index(users,EMAIL_PATH,username_or_email);

    return cweb.response.send_text("ok",200);



}