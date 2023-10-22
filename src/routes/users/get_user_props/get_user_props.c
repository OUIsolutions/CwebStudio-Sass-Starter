

CwebHttpResponse *get_user_props(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate_root(request,entries,database);
    if(auth.error){
        return  auth.response_error;
    }

    char *username_or_email = obj.getString(entries, USERNAME_OR_EMAIL_ENTRIE);
    obj.set_default(entries,INCLUDE_TOKEN_ENTRIE,hash.newBool(false));
    bool include_tokens = obj.getBool_converting(entries,INCLUDE_TOKEN_ENTRIE);



    CHash_catch(entries){
        return send_entrie_error(request, entries);
    }

    DtwResource *user_found = find_user_by_username_or_email(database,username_or_email);


    if(!user_found){
        return send_error(
                request,
                NOT_FOUND,
                USER_NOT_EXIST,
                USER_NOT_EXIST_MENSSAGE,
                username_or_email
        );
    }


    CHashObject  *description = describe_user(user_found,include_tokens);
    return send_chash_cleaning_memory(description, HTTP_OK);

}