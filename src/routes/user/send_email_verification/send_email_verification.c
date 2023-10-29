

CwebHttpResponse *send_email_verification_route(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate(request,entries,database);
    if(auth.error){
        return  auth.response_error;
    }

    DtwResource *user = auth.user;

    bool verified = resource.get_bool_from_sub_resource(user,VERIFIED_PATH);
    if(verified){
        return send_error(
                request,
                CONFLICT,
                WRONG_PASSWORD,
                WRONG_PASSWORD_MENSSAGE
        );
    }


    DtwHash *verification = newDtwHash();
    dtw.hash.digest_string(
            verification,
            resource.get_string_from_sub_resource(user,PASSWORD_PATH)
    );
    char *email = resource.get_string_from_sub_resource(user,EMAIL_PATH);

    dtw.hash.digest_string(
            verification,
           email
    );

    dtw.hash.digest_long(verification,time(NULL));
    CTextStack *verification_stack = newCTextStack_string(verification->hash);
    stack.self_substr(verification_stack,0,SHA_SIZE);

    char *username = resource.get_string_from_sub_resource(user,USERNAME_PATH);

    bool sending_result = send_email_verification(email,username,verification_stack->rendered_text);
    if(!sending_result){
        stack.free(verification_stack);
        dtw.hash.free(verification);
        return send_error(
                request,
                NOT_FOUND,
                COULD_NOT_SEND_EMAIL,
                COULD_NOT_SEND_EMAIL_MESSAGE
        );
    }

    resource.set_string_in_sub_resource(user,verification_stack->rendered_text,VERIFICATION_PATH);


    stack.free(verification_stack);
    dtw.hash.free(verification);

    CHashObject *response = newCHashObject(
            CODE_KEY,hash.newNumber(INTERNAL_OK),
            MESSAGE_KEY,hash.newString(EMAIL_SENDED)
    );
    commit_transaction(database);

    return send_chash_cleaning_memory(response,HTTP_CREATED);




}