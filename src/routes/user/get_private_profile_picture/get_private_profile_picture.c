

CwebHttpResponse *get_private_profile_picture(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate(request,entries,database);
    if(auth.error){
        return  auth.response_error;
    }
    DtwResource *user = auth.user;

    obj.set_default(entries, INCLUDE_TOKEN_ENTRE, hash.newBool(false));
    bool include_tokens = obj.getBool_converting(entries, INCLUDE_TOKEN_ENTRE);
    char *password = NULL;
    if(include_tokens){
            password = obj.getString(entries, PASSWORD_ENTRE);
    }
    CHash_catch(entries){
        return send_entrie_error(request, entries);
    }

    if(include_tokens){
        if(!password_are_equal(user, password)){
            return send_error(
                    request,
                    FOREBIDEN,
                    WRONG_PASSWORD,
                    WRONG_PASSWORD_MENSSAGE
            );
        }
    }

    CHashObject  *description = describe_user(user,include_tokens,false);
    return send_chash_cleaning_memory(description, HTTP_OK);

}