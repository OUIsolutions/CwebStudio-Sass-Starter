

CwebHttpResponse *send_error( CwebHttpRequest *request,int status, int internalcode,  const char *format,...){

    char buffer[1000]= {0};
    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);


    CHashObject * response = newCHashObject(
            "mensage",hash.newString(buffer),
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




CwebHttpResponse *send_entrie_error(CwebHttpRequest  *request, CHashObject *entries){

    validator.generate_custom_error_cleaning_args(entries, newCHashArray(

            newCHashObject(
                    "code",hash.newNumber(CHASH_ELEMENT_NOT_EXIST),
                    "message",hash.newString("entrie #key# not found in headders/paramns")
            ),

            newCHashObject(
                    "code",hash.newNumber(CHASH_HIGHER_THAN_MIN),
                    "message",hash.newString("entire #key# its higher than  #max#")
            ),

            newCHashObject(
                    "code",hash.newNumber(CHASH_LOWER_NUMBER),
                    "message",hash.newString("entire #key# its lower than  #min#")
            )
    ));

    char *menssage = hash.get_error_menssage(entries);

    CwebHttpResponse  *response = send_error(
            request,
            BAD_REQUEST,
            ENTRY_ERROR,
            menssage
            );
    return  response;
}

