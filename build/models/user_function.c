

CwebHttpResponse *function_name(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate(request,entries,database);
    if(auth.error){
        return  auth.response_error;
    }

    DtwResource *user = auth.user;


    CHash_catch(entries){
        return send_entrie_error(request, entries);
    }
   
    CHashObject *response = newCHashObject(
            CODE_KEY,hash.newNumber(INTERNAL_OK),
            MESSAGE_KEY,hash.newString("route ok")
    );
    resource.commit(database);

    return send_chash_cleaning_memory(response,HTTP_OK);

}
