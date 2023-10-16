

CwebHttpResponse *get_self_props(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate(request,entries,database);
    if(auth.error){
        return  auth.response_error;
    }
    DtwResource *user = auth.user;


    return cweb.response.send_text("self props",200);
}