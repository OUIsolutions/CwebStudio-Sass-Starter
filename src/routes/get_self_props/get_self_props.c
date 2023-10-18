

CwebHttpResponse *get_self_props(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate(request,entries,database);
    if(auth.error){
        return  auth.response_error;
    }
    DtwResource *user = auth.user;

    obj.set_default(entries,INCLUDE_TOKEN_ENTRIE,hash.newBool(false));
    bool include_tokens = obj.getBool(entries,INCLUDE_TOKEN_ENTRIE);
    char *password = NULL;
    if(include_tokens){
            password = obj.getString(entries,PASSWORD_ENTRIE);
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

    CHashObject  *description = describe_user(user,true);
    return send_chash_cleaning_memory(description, HTTP_OK);

}