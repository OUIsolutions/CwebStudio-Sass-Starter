

CwebHttpResponse *get_self_props(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate(request,entries,database);
    if(auth.error){
        return  auth.response_error;
    }
    DtwResource *user = auth.user;
    CHashObject  *description = describe_user(user,true);
    return send_chash_cleaning_memory(description, HTTP_OK);

}