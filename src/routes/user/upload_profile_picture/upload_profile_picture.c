

CwebHttpResponse *upload_profile_picture(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate(request,entries,database);
    if(auth.error){
        return  auth.response_error;
    }
    DtwResource *user = auth.user;

    obj.set_default(entries, PUBLIC_ENTRE, hash.newBool(false));
    bool public = obj.getBool_converting(entries, PUBLIC_ENTRE);

    CHash_catch(entries){
        return send_entrie_error(request, entries);
    }

    cweb.request.represent(request);

    unsigned char *body =  cweb.request.read_content(request, MAX_PROFILE_PICTURE);

    if(!body){
        return send_error(
                request,
                NOT_FOUND,
                PROFILE_PICTURE_NOT_PROVIDED,
                PROFILE_PICTURE_NOT_PROVIDED_MESSAGE
        );
    }

    CHash *response_hash = newCHashObject(
            CODE_KEY,hash.newNumber(INTERNAL_OK),
            MESSAGE_KEY,PICTURE_UPLOADED
    );

    return send_chash_cleaning_memory(response_hash,HTTP_CREATED);

}