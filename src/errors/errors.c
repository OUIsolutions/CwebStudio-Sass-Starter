

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
