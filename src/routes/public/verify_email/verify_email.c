

CwebHttpResponse *public_verify_email_route(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    char *user_id = obj.getString(entries,USER_ID_ENTRE);
    char *verification_key = obj.getString(entries, VERIFICATION_KEY_ENTRE);
    CHash_catch(entries){
        return send_entrie_error(request, entries);
    }

    DtwResource *user = find_user_by_id(database,user_id);
    if(!user){
        return send_error(
                request,
                NOT_FOUND,
                USER_NOT_EXIST,
                USER_NOT_EXIST_MENSSAGE,
                user_id
        );
    }
    DtwResource *real_verification =resource.sub_resource(user,VERIFICATION_PASSWORD_PATH);
    char *real_verification_key = resource.get_string(real_verification);

    if(!strings_equal(verification_key, real_verification_key)){
        return send_error(
                request,
                NOT_FOUND,
                USER_NOT_EXIST,
                VERIFICATION_KEY_ITS_WRONG_MESSAGE,
                verification_key
        );
    }
    resource.set_bool_in_sub_resource(user,true,VERIFIED_PATH);
    resource.destroy(real_verification);

    commit_transaction(database);

    CHashObject *response = newCHashObject(
            CODE_KEY,hash.newNumber(INTERNAL_OK),
            MESSAGE_KEY,hash.newString(USER_VERIFIED)
    );
    resource.commit(database);

    return send_chash_cleaning_memory(response,HTTP_OK);

}
