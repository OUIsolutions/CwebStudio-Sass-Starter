

CwebHttpResponse *send_email_verification_route(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){
    Autentication  auth = autenticate(request,entries,database);
    DtwResource_catch(database){
        return NULL;
    }
    if(auth.error){
        return  auth.response_error;
    }

    char *host = obj.getString(entries,HOST_ENTRIE);

    CHash_catch(entries){
        return send_entrie_error(request, entries);
    }
    DtwResource *user = auth.user;
    UniversalGarbage *garbage = newUniversalGarbage();

    bool verified = resource.get_bool_from_sub_resource(user,VERIFIED_PATH);
    DtwResource_catch(database){
        UniversalGarbage_free(garbage);
        return NULL;
    }
    if(verified){
        UniversalGarbage_free(garbage);
        return send_error(
                request,
                CONFLICT,
                USER_IS_ALREDY_VERIFIED,
                USER_IS_ALREDY_VERIFIED_MESSAGE
        );
    }

    DtwHash *verification = newDtwHash();
    UniversalGarbage_add(garbage, DtwHash_free,verification);

    dtw.hash.digest_string(
            verification,
            resource.get_string_from_sub_resource(user,PASSWORD_PATH)
    );
    char *email = resource.get_string_from_sub_resource(user,EMAIL_PATH);
    DtwResource_catch(database){
        UniversalGarbage_free(garbage);
        return NULL;
    }
    dtw.hash.digest_string(
            verification,
           email
    );

    dtw.hash.digest_long(verification,time(NULL));

    CTextStack *verification_stack = newCTextStack_string(verification->hash);
    UniversalGarbage_add(garbage,stack.free,verification_stack);

    stack.self_substr(verification_stack,0,SHA_SIZE);

    char *username = resource.get_string_from_sub_resource(user,USERNAME_PATH);
    DtwResource_catch(database){
        UniversalGarbage_free(garbage);
        return NULL;
    }

    CTextStack  *verification_url = construct_verification_url(
            user->name,
            verification_stack->rendered_text,
            host
            );

    UniversalGarbage_add(garbage,stack.free,verification_url);

    bool sending_result = send_email_verification(
            email,
            username,
            verification_url->rendered_text
            );


    resource.set_string_in_sub_resource(user,verification_stack->rendered_text,VERIFICATION_PASSWORD_PATH);


    UniversalGarbage_free(garbage);
    commit_transaction(database);


    if(!sending_result){
        return send_error(
                request,
                NOT_FOUND,
                COULD_NOT_SEND_EMAIL,
                COULD_NOT_SEND_EMAIL_MESSAGE
        );
    }

    CHashObject *response = newCHashObject(
            CODE_KEY,hash.newNumber(INTERNAL_OK),
            MESSAGE_KEY,hash.newString(EMAIL_SENDED)
    );

    return send_chash_cleaning_memory(response,HTTP_CREATED);


}