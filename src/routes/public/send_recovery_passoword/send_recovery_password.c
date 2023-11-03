

CwebHttpResponse *send_recovery_password_route(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    char *username_or_email = obj.getString(entries, LOGIN);

    CHash_catch(entries){
        return send_entrie_error(request, entries);
    }

    DtwResource *user = find_user_by_username_or_email(database,username_or_email);

    if(!user){
        return send_error(
                request,
                NOT_FOUND,
                USER_NOT_EXIST,
                USER_NOT_EXIST_MENSSAGE,
                username_or_email
        );
    }
    UniversalGarbage *garbage =newUniversalGarbage();
    DtwHash *dt_hash = newDtwHash();
    UniversalGarbage_add(garbage, DtwHash_free,dt_hash);

    char *password = resource.get_string_from_sub_resource(user,PASSWORD_PATH);
    dtw.hash.digest_string(dt_hash,password);
    dtw.hash.digest_long(dt_hash,time(NULL));

    CTextStack * formated_hash = newCTextStack_string(dt_hash->hash);
    UniversalGarbage_add(garbage,stack.free,formated_hash);

    stack.self_substr(formated_hash,0,SHA_SIZE);

    char *email = resource.get_string_from_sub_resource(user,EMAIL_PATH);
    char *username = resource.get_string_from_sub_resource(user,USERNAME_PATH);

    bool sending_result = send_email_verification(
            email,
            username,
            formated_hash->rendered_text
    );

    resource.set_string_in_sub_resource(user,formated_hash->rendered_text,RECOVERY_PASSWORD_PATH);


    UniversalGarbage_free(garbage);
    commit_transaction(database);


    if(!sending_result){
        return send_error(
                request,
                NOT_FOUND,
                COULD_NOT_SEND_EMAIL,
                COULD_NOT_SEND_RECOVERY_EMAIL
        );
    }

    CHashObject *response = newCHashObject(
            CODE_KEY,hash.newNumber(INTERNAL_OK),
            MESSAGE_KEY,hash.newString(RECOVERY_KEY_SENDED)
    );

    return send_chash_cleaning_memory(response,HTTP_CREATED);
}
