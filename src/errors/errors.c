

CwebHttpResponse *send_error( CwebHttpRequest *request,int status, int internalcode,  const char *menssage){

    CHashObject * response = newCHashObject(
            "mensage",hash.newString(menssage),
            "code",hash.newNumber(internalcode)
            );

    //these is for front end usage
    char * always200 = cweb.request.get_param(request,"always200");
    if(always200){
        if(strcmp(always200,"true") == 0){
            return send_chash_cleaning_memory(response,HTTP_OK);
        }
    }
    return send_chash_cleaning_memory(response,status);
}




CwebHttpResponse *send_entrie_error_cleaning_memory(CwebHttpRequest  *request, CHashObject *entries){

    validator.generate_custom_error_cleaning_args(entries, newCHashArray(
            newCHashObject(
                    "code",hash.newNumber(CHASH_NOT_EXIST),
                    "message",hash.newString("element of key #key# not found in headders/paramns")
                    )
            )
   );
            
    char *menssage = hash.get_error_menssage(entries);

    CwebHttpResponse  *response = send_error(
            request,
            BAD_REQUEST,
            ENTRY_ERROR,
            menssage
            );
    hash.free(entries);
    return  response;
}

