





CwebHttpResponse *create_token(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){
    aply_path_protection(entries,USERNAME_OR_EMAIL);
    char *username_or_email = obj.getString(entries,USERNAME_OR_EMAIL);
    char *password = obj.getString(entries,PASSWORD);

    obj.set_default(entries, EXPIRATION, hash.newNumber(DEFAULT_EXPIRATION));
    long expiration = (long)obj.getNumber_converting(entries, EXPIRATION);


    if(expiration != -1 && expiration <=0){
        validator.raise_error_by_key(entries,
                                     EXPIRATION,
                                     INVALID_EXPIRATION,
                                     "param #reference# at headders/paramns is not a valid expiration time "
                                     "use -1 for infinity tokens or 1 or more for finite tokens",
                                     NULL
        );
    }
    obj.set_default(entries, ALLOW_RENEW_PATH, hash.newBool(DEFAULT_ALLOW_RENEW));
    bool allow_renew = obj.getBool_converting(entries, ALLOW_RENEW_PATH);


    CHash_catch(entries){
        return send_entrie_error(request, entries);
    }


    DtwResource *user = find_user_by_username_or_email(database,username_or_email,true);

    if(!user){
        return send_error(
                request,
                NOT_FOUND,
                USER_NOT_EXIST,
                USER_NOT_EXIST_MENSSAGE,
                username_or_email
        );
    }

    if(!password_are_equal(user, password)){
        return send_error(
                request,
                FOREBIDEN,
                WRONG_PASSWORD,
                WRONG_PASSWORD_MENSSAGE
        );
    }

    //the token assignature will be formed by the user password + time + id
    char *user_id = user->name;

    char *token = create_token_string(user_id,password);

    if(expiration == -1){
        set_infinity_token(user, token);
    }

    if(expiration > 0){
        set_finity_token(user, token, allow_renew, expiration);
    }




    resource.commit(database);
    CHash *response_hash = newCHashObject(
            "code",hash.newNumber(INTERNAL_OK),
            "hash",hash.newString(token)
            );
    free(token);
    return send_chash_cleaning_memory(response_hash,HTTP_CREATED);

}