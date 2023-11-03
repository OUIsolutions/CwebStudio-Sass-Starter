

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

    char *password = resource.get_string_from_sub_resource(user,PASSWORD_PATH);



    CHashObject *response = newCHashObject(
            CODE_KEY,hash.newNumber(INTERNAL_OK),
            MESSAGE_KEY,hash.newString("route ok")
    );
    resource.commit(database);

    return send_chash_cleaning_memory(response,HTTP_OK);

}
